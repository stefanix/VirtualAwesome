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

#ifndef VATOUCHKIT_VIDEO_GRABBER_DC1394
#define VATOUCHKIT_VIDEO_GRABBER_DC1394

#include <memory.h>
#include <stdint.h>
#include <dc1394/dc1394.h>
#include <inttypes.h>

#include <osg/Notify>
#include <osg/Image>
#include <va/Constants.h>


namespace vaTouchkit {


class VideoGrabber {

	public :

		VideoGrabber( int w, int h );
		virtual ~VideoGrabber();

        int getWidth() { return _width; }
        int getHeight() { return _height; }

		void listDevices();
		bool selectDevice( int index );
		bool selectDeviceByGuid( uint64_t guid );
		bool isFrameNew();
		void grabFrameInto( osg::Image* image );


		// libdc1394 Stuff
        //
		void setBrightness( int value );
		int getBrightness();
		void setExposure( int value );
		int getExposure();
		void setShutter( int value );
		int getShutter();

	protected:

		int		  _height;
		int		  _width;
        int       _depth;           //channels
		bool 	  _bGrabberReady;
		bool 	  _bIsFrameNew;

		// libdc1394 Stuff
        //
		dc1394camera_t*       camera;
		dc1394featureset_t    features;
		dc1394framerates_t    framerates;
		dc1394video_modes_t   video_modes;
		dc1394framerate_t     framerate;
		dc1394video_mode_t    video_mode;
		dc1394color_coding_t  color_coding;
		int                   packet_size;
		dc1394video_frame_t*  frame;
		dc1394_t*             driver;
		dc1394camera_list_t*  deviceList;
		dc1394error_t         err;

};



}
#endif

