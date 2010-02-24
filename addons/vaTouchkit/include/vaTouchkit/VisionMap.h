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
* This class handles the calibration of the video feed.
* With it you can define a mapping that takes into account
* various transformations like translation, rotation, scale,
* warping, barrel distortion.
*/

#ifndef VATOUCHKIT_VISIONMAP
#define VATOUCHKIT_VISIONMAP

#include <vector>
#include <cv.h>
#include <va/Constants.h>
#include <va/Node.h>
#include <va/Widget.h>
#include <va/VertexGeometry.h>
#include <vaOpencv/Image.h>

namespace vaTouchkit {


class VisionMap;


class QuadHandle : public va::Widget {
    public:        
    
        QuadHandle( VisionMap* visionMap, int corner );
        void reshape();
        using Widget::reshape;
        
        void touchDown( va::Touch& touch );
        void touchMove( va::Touch& touch );
        void touchUp( va::Touch& touch );
        
    protected:
        osg::ref_ptr<VisionMap> _visionMap;
        int _corner;
};


class VisionMap : public va::Node {

	public :
		
        enum Corner {TOP_LEFT, TOP_RIGHT, BOTTOM_RIGHT, BOTTOM_LEFT};
        
		VisionMap(int w, int h);
		virtual ~VisionMap();
        
        void setCorner( Corner corner, float x, float y );
        void setCorner( Corner corner, const osg::Vec3& vertex );
        const osg::Vec3& getCorner( Corner corner );

        void mapPoint(int& x, int& y);        
		virtual bool isClipped( int x, int y );
		virtual bool isClipped( osg::Vec2f point );
        void setMapTouchEvents( bool bMap) {_bMapTouchEvents = bMap;}        
        bool getMapTouchEvents() {return _bMapTouchEvents;}

		// actually warps the image according to the 
        // mapping -- mostly used for debugging
		virtual void apply( vaOpencv::Image* image );
        
        	
	protected:
    	friend class QuadHandle;
    	int _width;
    	int _height;
        float _magnitudeScale;
        bool _bMapTouchEvents;                           
        osg::ref_ptr<va::VertexGeometry> _warpQuad;
        osg::ref_ptr<QuadHandle> _warpHandleBL;
        osg::ref_ptr<QuadHandle> _warpHandleBR;
        osg::ref_ptr<QuadHandle> _warpHandleTR;
        osg::ref_ptr<QuadHandle> _warpHandleTL;
        
        CvPoint2D32f _cvsrc[4];
        CvPoint2D32f _cvdst[4];
        CvMat* _translate;
        
        IplImage*  _mapToTargetX;
        IplImage*  _mapToTargetY; 
        IplImage*  _mapToSourceX;
        IplImage*  _mapToSourceY; 

        std::vector<va::RawTouchHandler*> _eventHandlers;
        
        void generateMap();
        bool withinTriangle( osg::Vec2f p, osg::Vec2f A, osg::Vec2f B, osg::Vec2f C );
    	                
};



}
#endif

