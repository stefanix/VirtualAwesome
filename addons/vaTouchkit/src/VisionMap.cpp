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

#include <vaTouchkit/VisionMap.h>
#include <osg/BoundsChecking>

using namespace vaTouchkit;



// QuadHandle
//

QuadHandle::QuadHandle( VisionMap* visionMap, int corner ) {
    _visionMap = visionMap;
    _corner = corner;
    _width = _height= 40;
    setPivot(20,20,0);
    setBackgroundColor(0.6f, 0.0f, 0.0f, 0.3f);
    setBorderColor(0.6f, 0.0f, 0.0f, 1.0f);
    reshape();
}

void QuadHandle::reshape() {
    _background->clearVertices();
    _background->addRoundedRect(0.0f, 0.0f, _width, _height, 4.0f);
	_border->setOsgVertexCount(_background->getOsgVertexCount());
}

void QuadHandle::touchDown( va::Touch& touch ) {}  
void QuadHandle::touchMove( va::Touch& touch ) {
    if( isDragging(touch) ) {
        const osg::Vec3& pos = getPosition();
        const osg::Vec3& dragDelta = getWorldDragDelta(touch);
        
        if( (VisionMap::Corner)_corner == VisionMap::BOTTOM_LEFT ){
            setPosition( osg::clampBetween(pos.x()+dragDelta.x(), 0.0f, 0.5f*_visionMap->_width),
                         osg::clampBetween(pos.y()+dragDelta.y(), 0.0f, 0.5f*_visionMap->_height),
                         pos.z()+dragDelta.z() );
        } else if( (VisionMap::Corner)_corner == VisionMap::BOTTOM_RIGHT ){
            setPosition( osg::clampBetween(pos.x()+dragDelta.x(), 0.5f*_visionMap->_width, (float)_visionMap->_width),
                         osg::clampBetween(pos.y()+dragDelta.y(), 0.0f, 0.5f*_visionMap->_height),
                         pos.z()+dragDelta.z() );
        } else if( (VisionMap::Corner)_corner == VisionMap::TOP_RIGHT ){
            setPosition( osg::clampBetween(pos.x()+dragDelta.x(), 0.5f*_visionMap->_width, (float)_visionMap->_width),
                         osg::clampBetween(pos.y()+dragDelta.y(), 0.5f*_visionMap->_height, (float)_visionMap->_height),
                         pos.z()+dragDelta.z() );
        } else if( (VisionMap::Corner)_corner == VisionMap::TOP_LEFT ){
            setPosition( osg::clampBetween(pos.x()+dragDelta.x(), 0.0f, 0.5f*_visionMap->_width),
                         osg::clampBetween(pos.y()+dragDelta.y(), 0.5f*_visionMap->_height, (float)_visionMap->_height),
                         pos.z()+dragDelta.z() );
		}
        
        _visionMap->setCorner((VisionMap::Corner)_corner, getPosition());
    }
}
void QuadHandle::touchUp( va::Touch& touch ) {}





// VisionMap
//

VisionMap::VisionMap( int w, int h ){
	_width = w;
    _height= h;
    _magnitudeScale = 1.0f;
	_bMapTouchEvents = true;    
    
    _translate = cvCreateMat( 3,3, CV_32FC1 );
    
    CvSize csize = cvSize( _width, _height );
    _mapToTargetX = cvCreateImage( csize, IPL_DEPTH_32F, 1 );
    _mapToTargetY = cvCreateImage( csize, IPL_DEPTH_32F, 1 );
    _mapToSourceX = cvCreateImage( csize, IPL_DEPTH_32F, 1 );
    _mapToSourceY = cvCreateImage( csize, IPL_DEPTH_32F, 1 );
    
    _warpQuad = new va::VertexGeometry();
    _warpQuad->setMode(GL_LINE_LOOP);
    _warpQuad->setColor(0.6f, 0.0f, 0.0f, 1.0f);
    _warpQuad->addVertex(0,0,0);
    _warpQuad->addVertex(_width,0,0);
    _warpQuad->addVertex(_width,_height,0);
    _warpQuad->addVertex(0,_height,0);
    _geode->addDrawable(_warpQuad->getOsgGeometry().get());
    
    _warpHandleBL = new QuadHandle(this, VisionMap::BOTTOM_LEFT);
    _warpHandleBR = new QuadHandle(this, VisionMap::BOTTOM_RIGHT);
    _warpHandleTR = new QuadHandle(this, VisionMap::TOP_RIGHT);
    _warpHandleTL = new QuadHandle(this, VisionMap::TOP_LEFT);
    _warpHandleBL->setPosition(0,0,0);
    _warpHandleBR->setPosition(_width,0,0);
    _warpHandleTR->setPosition(_width,_height,0);
    _warpHandleTL->setPosition(0,_height,0);
    addChild(_warpHandleBL);
    addChild(_warpHandleBR);
    addChild(_warpHandleTR);
    addChild(_warpHandleTL);
    
    generateMap();
}



VisionMap::~VisionMap(){
    cvReleaseMat( &_translate );
    cvReleaseImage( &_mapToTargetX );
    cvReleaseImage( &_mapToTargetY );
    cvReleaseImage( &_mapToSourceX );
    cvReleaseImage( &_mapToSourceY );
}



void VisionMap::setCorner( Corner corner, float x, float y ){
	setCorner(corner, osg::Vec3(x,y,0.0f));
}
void VisionMap::setCorner( Corner corner, const osg::Vec3& vertex ){
	switch (corner) {
        case VisionMap::BOTTOM_LEFT:
    		_warpQuad->setVertex(0, vertex);
            break;
        case VisionMap::BOTTOM_RIGHT:
    		_warpQuad->setVertex(1, vertex);
            break;
        case VisionMap::TOP_RIGHT:
    		_warpQuad->setVertex(2, vertex);
            break;
        case VisionMap::TOP_LEFT:
    		_warpQuad->setVertex(3, vertex);
            break;
        default:
            break;
    }
    
    generateMap();
}
const osg::Vec3& VisionMap::getCorner( Corner corner ){
	switch (corner) {
        case VisionMap::BOTTOM_LEFT:
    		return _warpQuad->getVertex(0);
            break;
        case VisionMap::BOTTOM_RIGHT:
    		return _warpQuad->getVertex(1);
            break;
        case VisionMap::TOP_RIGHT:
    		return _warpQuad->getVertex(2);
            break;
        case VisionMap::TOP_LEFT:
    		return _warpQuad->getVertex(3);
            break;
        default:
        	osg::notify(osg::WARN) << "in getCorner, invalid corner argument" << std::endl;
        	return _warpQuad->getVertex(0);
            break;
    }
}



bool VisionMap::isClipped( int x, int y ) {
	return isClipped(osg::Vec2f(x,y));
}
bool VisionMap::isClipped( osg::Vec2f point ) {

    //check if point is outside quad
    
    bool withinTri1 = withinTriangle( point,
    	osg::Vec2f( getCorner(VisionMap::BOTTOM_LEFT).x(), getCorner(VisionMap::BOTTOM_LEFT).y() ),
    	osg::Vec2f( getCorner(VisionMap::BOTTOM_RIGHT).x(), getCorner(VisionMap::BOTTOM_RIGHT).y() ),
        osg::Vec2f( getCorner(VisionMap::TOP_LEFT).x(), getCorner(VisionMap::TOP_LEFT).y() )
    );

    bool withinTri2 = withinTriangle( point,
        osg::Vec2f( getCorner(VisionMap::TOP_LEFT).x(), getCorner(VisionMap::TOP_LEFT).y() ),
    	osg::Vec2f( getCorner(VisionMap::BOTTOM_RIGHT).x(), getCorner(VisionMap::BOTTOM_RIGHT).y() ),
    	osg::Vec2f( getCorner(VisionMap::TOP_RIGHT).x(), getCorner(VisionMap::TOP_RIGHT).y() )
    );
        
    return !(withinTri1 || withinTri2);
}

bool VisionMap::withinTriangle( osg::Vec2f p, osg::Vec2f A, osg::Vec2f B, osg::Vec2f C ){
	// Barycentric Technique
	// http://www.blackpawn.com/texts/pointinpoly/default.html
    
    // Compute vectors
	osg::Vec2f v0 = C - A;
    osg::Vec2f v1 = B - A;
    osg::Vec2f v2 = p - A;
    
    // Compute dot products
    float dot00 = v0 * v0;
    float dot01 = v0 * v1;
    float dot02 = v0 * v2;
    float dot11 = v1 * v1;
    float dot12 = v1 * v2;
    
    // Compute barycentric coordinates
    float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
    float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

    // Check if point is in triangle
    return (u > 0) && (v > 0) && ((u+v) < 1);          
}


void VisionMap::mapPoint(int& x, int& y){
    int x_ = x;
    x = ((float *)(_mapToTargetX->imageData + y*_mapToTargetX->widthStep))[x_];
    y = ((float *)(_mapToTargetY->imageData + y*_mapToTargetY->widthStep))[x_];
}


void VisionMap::apply( vaOpencv::Image* image ) {
    image->remap( _mapToSourceX, _mapToSourceY );
}


void VisionMap::generateMap() {
    cvSetZero( _translate );
    
    //calculate a gereral scaling factor
	float source_diagonal_square = _width*_width + _height*_height;
	float target_diagonal_square = getCorner(VisionMap::TOP_RIGHT).x()*getCorner(VisionMap::TOP_RIGHT).x()
                                 + getCorner(VisionMap::TOP_RIGHT).y()*getCorner(VisionMap::TOP_RIGHT).y();
    _magnitudeScale = (target_diagonal_square) / (source_diagonal_square);
        
    // Prime maps with a pixel value according to location.
    // After transforming them the values will always point
    // to the place where the source pixel should be taken from.
    //
    for( int i=0;i<_mapToTargetX->height;i++ ) {
        for( int j=0;j<_mapToTargetX->width;j++ ) {
            ((float *)(_mapToTargetX->imageData + i*_mapToTargetX->widthStep))[j] = (float)j;
        }
    }
    for( int i=0;i<_mapToTargetY->height;i++ ) {
        for( int j=0;j<_mapToTargetY->width;j++ ) {
            ((float *)(_mapToTargetY->imageData + i*_mapToTargetY->widthStep))[j] = (float)i;
        }
    }    

    _cvdst[0].x = 0;
    _cvdst[0].y = 0;
    _cvdst[1].x = _width;
    _cvdst[1].y = 0;
    _cvdst[2].x = _width;
    _cvdst[2].y = _height;
    _cvdst[3].x = 0;
    _cvdst[3].y = _height;

    _cvsrc[0].x = getCorner(VisionMap::BOTTOM_LEFT).x();
    _cvsrc[0].y = getCorner(VisionMap::BOTTOM_LEFT).y();
    _cvsrc[1].x = getCorner(VisionMap::BOTTOM_RIGHT).x();
    _cvsrc[1].y = getCorner(VisionMap::BOTTOM_RIGHT).y();
    _cvsrc[2].x = getCorner(VisionMap::TOP_RIGHT).x();
    _cvsrc[2].y = getCorner(VisionMap::TOP_RIGHT).y();
    _cvsrc[3].x = getCorner(VisionMap::TOP_LEFT).x();
    _cvsrc[3].y = getCorner(VisionMap::TOP_LEFT).y();
    
    cvWarpPerspectiveQMatrix( _cvsrc, _cvdst, _translate );
    
    cvWarpPerspective( _mapToTargetX, _mapToSourceX, _translate );
    cvWarpPerspective( _mapToTargetY, _mapToSourceY, _translate );
    
    // Also generate a revese map in _mapToTargetX, _mapToTargetY.
    // This is used for mapping points.
    int pX, pY;
    for( int i=0;i<_mapToSourceX->height;i++ ) {
        for( int j=0;j<_mapToSourceX->width;j++ ) {
        	// get what it points to            
            pX = (int)((float *)(_mapToSourceX->imageData + i*_mapToSourceX->widthStep))[j];
            pY = (int)((float *)(_mapToSourceY->imageData + i*_mapToSourceY->widthStep))[j];
            
            if( pX>=0 && pX<_width && pY>=0 && pY<_height ) {
                // set reverse map
                ((float *)(_mapToTargetX->imageData + pY*_mapToTargetX->widthStep))[pX] = (float)(j);
                ((float *)(_mapToTargetY->imageData + pY*_mapToTargetY->widthStep))[pX] = (float)(i);
			}            
        }
    }    
    
}


