/*
* Copyright 2009 NOR_/D Labs <http://labs.nortd.com>
*
* This file is part of VirtualAwesome.
* VirtualAwesome is free software: you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public License 
* as published by the Free Software Foundation, either version 3 of 
* the License, or (at your option) any later version. For details
* see <http://www.gnu.org/licenses/>.
*
* * *
* The BlobTracker matches blobs between frames.
* The blobs in the current frame choose their id based on which
* previous blob is closest to them. Closest matches are
* considered first.
*
* The trick is to sort all possible pairs based on distance
* and start assigning the closest pairs first. Distances over a
* certain threshold proximity are discarded.
*
*/

#include <vaTouchkit/BlobTracker.h>


using namespace vaTouchkit;



BlobTracker::BlobTracker( int w, int h, VisionMap* visionMap )
  : _width(w),
    _height(h),
    _scaleX(1.0f),
    _scaleY(1.0f),
	_maxDistance(0.2*_width),
    _maxGhostSurvival(1),
    _runningId(0),
    _smoothCenter(0.3f),
    _smoothRadius(0.6f)
{
	_visionMap = visionMap;
}



BlobTracker::~BlobTracker(){

}

void BlobTracker::track( ContourFinder* finder ){

	// copy contour data into Blobs and add them to blob history
	_history.push_back(std::vector<Blob*>());
    for(unsigned int i=0; i<finder->contours.size(); i++) {
        Contour& contour = finder->contours[i];
        
        //skip contours clipped by the visionMap
        // only when in touch event mapping mode
        if ( _visionMap->getMapTouchEvents() ) {
            if (_visionMap->isClipped(contour.center)){
                continue;
            }
        }       

    	_history[_history.size()-1].push_back(
        	new Blob(contour.center.x(), contour.center.y(), contour.box.radius())
        );
    }    
    
    
    // limit length of history
	if( _history.size() > 2 ) {
    	// delete first entry
    	for(unsigned int i=0; i<_history[0].size(); ++i){
        	delete _history[0][i];  // del blob
        }
		_history.erase( _history.begin() );
	}
    
    // make sure we have something to correlate
    if (_history.size() < 2) {
        return;
    }


	//----------------------------- rematch previous to current blobs
    
	std::vector<Blob*>& blobsT0 = _history[_history.size()-1];
	std::vector<Blob*>& blobsT1 = _history[_history.size()-2]; 
        
    // assemble all possible blob matching pairs
    // total number is blobsT0.size() * blobsT1.size()
    for(unsigned int i=0; i<blobsT0.size(); i++) {
        for(unsigned int j=0; j<blobsT1.size(); j++) {
        	BlobPair _pair = BlobPair(blobsT0[i], blobsT1[j]);
            if (_pair.distance() < _maxDistance ) {
                _pairs.push_back(_pair);
            }
        }		
    }
    //std::cout << "pairs: " << _pairs.size() 
    //    << " (" << blobsT0.size() << "," << blobsT1.size() << ")" << std::endl;
    
    // sort by distance in ascending order
    // based on the < operator of BlobPair
    std::sort( _pairs.begin(), _pairs.end());
    
    // rematch ids
    // also set location history
    for(unsigned int i=0; i<_pairs.size(); i++) {
    	// skip if one of the blobs already got matched
    	if (_pairs[i].blobT0->id != -1 || _pairs[i].blobT1->_gotMatched) {
        	continue;
        }
        
        _pairs[i].blobT0->id = _pairs[i].blobT1->id == -1 ? getNextId() : _pairs[i].blobT1->id;
        //_pairs[i].blobT0->_centerT1 = _pairs[i].blobT1->center;
        //_pairs[i].blobT0->_centerT2 = _pairs[i].blobT1->_centerT1;
        _pairs[i].blobT1->_gotMatched = true;
        
        // apply smoothing
        _pairs[i].blobT0->center = _pairs[i].blobT0->center*(1-_smoothCenter) + _pairs[i].blobT1->center*_smoothCenter;
        _pairs[i].blobT0->radius = _pairs[i].blobT0->radius*(1-_smoothRadius) + _pairs[i].blobT1->radius*_smoothRadius;
    }
    
    // we are done with pairs
    _pairs.clear();
    
    // assemble blobs vector
    // this is done before ghost blobs are added to history
    _blobs.clear();
    for(unsigned int i=0; i<blobsT0.size(); ++i) {
    	_blobs.push_back(blobsT0[i]);
    }
    
    
    //----------------------------- fire events
    
    // new and moved blobs
    for(unsigned int i=0; i<blobsT0.size(); ++i) {
    	if (blobsT0[i]->id == -1) {
            // this is a new blob that did not get matched to a previous one
            // ==> new blob, assign next id, fire touchEnter, touchDown event
            // optionally we could call touchDown only at a certain blob size
            blobsT0[i]->id = getNextId();
            touchEnter( blobsT0[i]->id, 
                        blobsT0[i]->center.x(), 
                        blobsT0[i]->center.y(), 
                        blobsT0[i]->radius );
            touchDown( blobsT0[i]->id, 
                       blobsT0[i]->center.x(), 
                       blobsT0[i]->center.y(), 
                       blobsT0[i]->radius );

            
        } else {
        	// this is a blob that got matched
            // ==> moved blob, fire touchMove event
            touchMove( blobsT0[i]->id, 
                       blobsT0[i]->center.x(), 
                       blobsT0[i]->center.y(), 
                       blobsT0[i]->radius );
        }
    }    

    // disappeared blobs
    for(unsigned int i=0; i<blobsT1.size(); ++i) {
        if (blobsT1[i]->_gotMatched == false) {
            // this is an old blob that did not get matched to a new one
            // if we allow ghost blobs to stick around we do not fire
            // a touchLeave event right away but give the blob another 
            // chance for rematching in the next frame
            if (blobsT1[i]->_ghostCount < _maxGhostSurvival) {
                // make sure blob is still considered for 
                // matching in next frame
                blobsT1[i]->_ghostCount++;
                blobsT0.push_back(new Blob( *(blobsT1[i]) ));
            } else {
                // blob disappeared, fire touchUp, touchLeave event
                // optionally we could call touchUp when blob goes 
                // under a threshold size
                touchUp( blobsT1[i]->id, 
                         blobsT1[i]->center.x(), 
                         blobsT1[i]->center.y(), 
                         blobsT1[i]->radius );
                touchLeave( blobsT1[i]->id, 
                            blobsT1[i]->center.x(), 
                            blobsT1[i]->center.y(), 
                            blobsT1[i]->radius );
            }
        }
    }
        
}




// Call Handlers
//

void BlobTracker::touchEnter( int id, int x, int y, float magnitude ){
	if(_visionMap->getMapTouchEvents()) {
    	_visionMap->mapPoint(x,y);
    	//magnitude *= _magnitudeScale;
    }
    x *= _scaleX;
    y *= _scaleY;
    magnitude *= _scaleX;

    
    for(unsigned int j=0; j<_eventHandlers.size(); ++j) {
        _eventHandlers[j]->rawTouchEnter( id, x, y, magnitude );
    }    
}

void BlobTracker::touchDown( int id, int x, int y, float magnitude ){
	if(_visionMap->getMapTouchEvents()) {
    	_visionMap->mapPoint(x,y);
    	//magnitude *= _magnitudeScale;
    }
    x *= _scaleX;
    y *= _scaleY;
    magnitude *= _scaleX;

    for(unsigned int j=0; j<_eventHandlers.size(); ++j) {
        _eventHandlers[j]->rawTouchDown( id, x, y, magnitude );
    } 
}

void BlobTracker::touchMove( int id, int x, int y, float magnitude ){
	if(_visionMap->getMapTouchEvents()) {
    	_visionMap->mapPoint(x,y);
    	//magnitude *= _magnitudeScale;
    }
    x *= _scaleX;
    y *= _scaleY;
    magnitude *= _scaleX;

    for(unsigned int j=0; j<_eventHandlers.size(); ++j) {
        _eventHandlers[j]->rawTouchMove( id, x, y, magnitude );
    } 
}

void BlobTracker::touchUp( int id, int x, int y, float magnitude ){
	if(_visionMap->getMapTouchEvents()) {
    	_visionMap->mapPoint(x,y);
    	//magnitude *= _magnitudeScale;
    }
    x *= _scaleX;
    y *= _scaleY;
    magnitude *= _scaleX;

    for(unsigned int j=0; j<_eventHandlers.size(); ++j) {
        _eventHandlers[j]->rawTouchUp( id, x, y, magnitude );
    } 
}

void BlobTracker::touchLeave( int id, int x, int y, float magnitude ){
	if(_visionMap->getMapTouchEvents()) {
    	_visionMap->mapPoint(x,y);
    	//magnitude *= _magnitudeScale;
    }
    x *= _scaleX;
    y *= _scaleY;
    magnitude *= _scaleX;

    for(unsigned int j=0; j<_eventHandlers.size(); ++j) {
        _eventHandlers[j]->rawTouchLeave( id, x, y, magnitude );
    } 
}




// Get Blobs
//

unsigned int BlobTracker::getBlobNum() {
    return _blobs.size();
}

unsigned int BlobTracker::getBlobId(unsigned int i) {
	return _blobs[i]->id;
}

int BlobTracker::getBlobX(unsigned int i) {
	return _blobs[i]->center.x();
}

int BlobTracker::getBlobY(unsigned int i) {
	return _blobs[i]->center.y();
}

int BlobTracker::getBlobRadius(unsigned int i) {
	return _blobs[i]->radius;
}


void BlobTracker::addEventHandler( va::RawTouchHandler* handler ) {
    _eventHandlers.push_back(handler);
}


int BlobTracker::getNextId(){
	int ret = ++_runningId;
	return ret >= 0 ? ret : 0;
}
