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

#ifndef VATOUCHKIT_JPEG_GRABBER
#define VATOUCHKIT_JPEG_GRABBER


#include <string>
#include <sstream>
#include <iomanip>

#include <cv.h>
#include <osg/Image>
#include <osgDB/ReadFile>
#include <va/Constants.h>


namespace vaTouchkit {


class JpegGrabber {

	public :
		
		JpegGrabber( int w, int h );
		virtual ~JpegGrabber();
        
        int getWidth() { return _width; }
        int getHeight() { return _height; }
        
		bool selectJpegs( const std::string& fistJpeg, int numDigits, int start, int end );
		bool isFrameNew();
		void grabFrameInto( osg::Image* image );
        
        	
	protected:
                
		int		      _height;
		int		      _width;  
        int           _depth;             //channels 
		bool 	      _bGrabberReady;
		bool 	      _bIsFrameNew;
        unsigned int  _frameCounter;
		
        std::vector< osg::ref_ptr<osg::Image> >  _sequence;
};



}
#endif

