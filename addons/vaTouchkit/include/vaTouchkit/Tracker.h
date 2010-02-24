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

#ifndef VATOUCH_TRACKER
#define VATOUCH_TRACKER


#include <osg/Image>
#include <osg/Timer>
#include <osg/GraphicsContext>

#include <va/Constants.h>
#include <va/Node.h>
#include <va/ImageShape.h>
#include <va/PanelWidget.h>
#include <va/ButtonWidget.h>
#include <va/EventHandlers.h>
#include <vaOpencv/Image.h>

#include <vaTouchkit/VideoGrabber.h>
#include <vaTouchkit/JpegGrabber.h>
#include <vaTouchkit/AdaptiveFilter.h>
#include <vaTouchkit/ContourFinder.h>
#include <vaTouchkit/BlobTracker.h>
#include <vaTouchkit/VisionMap.h>


namespace vaTouchkit {


class Tracker : public va::Node,
                public va::ButtonHandler, public va::SliderHandler, public va::ToggleHandler {

	public :

		Tracker( int w, int h );
		virtual ~Tracker();
        
		int getWidth() { return _width; }
		int getHeight() { return _height; }
		void setBrightness( int value );
		int getBrightness();
		void setExposure( int value );
		int getExposure();
		void setShutter( int value );
		int getShutter();
        
        void setTargetResolution( int w, int h );
        void addEventHandler( va::RawTouchHandler* handler );          
        void setPlay( bool bPlay ){_bPlay = bPlay;}
        bool getPlay(){return _bPlay;}
        void resetBackground() {_filter->resetBackground();}
        void setSetupMode(bool bSetup);
        bool getSetupMode() {return _bSetupMode;}
        		
        
    	// live video
        //
		void listDevices();
		bool selectDevice( int index );
		//bool selectDeviceByGuid( unsigned long long guid );
        
        
        // jpeg video sequence
        bool selectJpegs( const std::string& fistJpeg, int numDigits, int start, int end );
        
        
        void update();
        void widget( va::ButtonWidget& button );
        void widget( va::SliderWidget& slider );
        void widget( va::ToggleWidget& toggle );                
        		
		
        // OSG stuff
        //
        osg::Image*  getOsgImage() { return _image->getOsgImage(); }
	
    
	protected:
                
		int	_width; 
		int _height;
        unsigned int _targetWidth;
		unsigned int _targetHeight;  
	
		bool _bNewFrame;
		bool _bSetupMode;
		bool _bPlay;
        
        VideoGrabber* _videoGrabber;
        JpegGrabber*  _jpegGrabber;
        
        vaOpencv::Image* _image;
        va::PanelWidget* _setupPanel;
        
        vaOpencv::Image* _afterAcquiringImg;
        va::ImageShape*  _afterAcquiringImgShape;
        
        osg::ref_ptr<VisionMap> _visionMap;

		AdaptiveFilter*  _filter;
        vaOpencv::Image* _afterFilteringImg;
        va::ImageShape*  _afterFilteringImgShape;
        
        ContourFinder*  _contourFinder;
        BlobTracker*  _blobTracker;
                        
        long _camFrameCount;
        int _camFps;
        int _dspTime;
        osg::Timer  _dspTimer;
        osg::Timer  _camFrameTimer;
                
};



}
#endif

