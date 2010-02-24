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
* 
*/

#ifndef VATOUCHKIT_BLOB_TRACKER
#define VATOUCHKIT_BLOB_TRACKER


#include <algorithm>
#include <osg/Notify>
#include <va/Constants.h>
#include <va/EventHandlers.h>
#include <vaTouchkit/ContourFinder.h>
#include <vaTouchkit/Contour.h>
#include <vaTouchkit/Blob.h>
#include <vaTouchkit/VisionMap.h>


namespace vaTouchkit {


class BlobTracker {

	public :
		        
		BlobTracker( int w, int h, VisionMap* visionMap );
		virtual ~BlobTracker();
        
        void setScale( float scaleX, float scaleY ) {_scaleX = scaleX; _scaleY = scaleY;}
        
		virtual void track( ContourFinder* finder );
                
        unsigned int getBlobNum();
        unsigned int getBlobId( unsigned int i );
        int getBlobX( unsigned int i );
        int getBlobY( unsigned int i );
        int getBlobRadius( unsigned int i );
        
        void addEventHandler( va::RawTouchHandler* handler );
        void setMotionSmoothing( float smoothing ) {_smoothCenter=smoothing;}
        
        	
	protected:
    	osg::ref_ptr<VisionMap> _visionMap;
    	int _width;
    	int _height;
    	float _scaleX;
        float _scaleY;
        float _maxDistance;
        int _maxGhostSurvival;
        int _runningId;
        float _smoothCenter;  //0-1 ... none-unlimited
        float _smoothRadius;  //0-1 ... none-unlimited
                
		std::vector< std::vector<Blob*> > _history;
		std::vector<BlobPair> _pairs;
        std::vector<Blob*> _blobs;
        std::vector<va::RawTouchHandler*> _eventHandlers;
        
        int getNextId();
        
        void touchEnter( int id, int x, int y, float magnitude );
        void touchDown( int id, int x, int y, float magnitude );
        void touchMove( int id, int x, int y, float magnitude );
        void touchUp( int id, int x, int y, float magnitude );
        void touchLeave( int id, int x, int y, float magnitude );
        void mapPoint(int& x, int& y);        
};



}
#endif

