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

#ifndef VATOUCHKIT_VIDEO_GRABBER_FLYCAPTURE
#define VATOUCHKIT_VIDEO_GRABBER_FLYCAPTURE

#include <FlyCapture/FlyCapture2.h>
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
		//bool selectDeviceByGuid( FlyCapture2::PGRGuid guid );
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

		// FlyCapture Stuff
        //
        FlyCapture2::Error                   err;
        FlyCapture2::BusManager		         busMgr;
        FlyCapture2::PGRGuid                 guid;
	    FlyCapture2::Camera          		 cam;
        FlyCapture2::CameraInfo              camInfo;
        FlyCapture2::Format7Info             fmt7Info;
        FlyCapture2::Format7ImageSettings    fmt7ImageSettings;
        FlyCapture2::Format7PacketInfo       fmt7PacketInfo;
        FlyCapture2::Property                frmRate;
	    FlyCapture2::Image			         rawImage;

        FlyCapture2::Mode                    k_fmt7Mode;
        FlyCapture2::PixelFormat             k_fmt7PixFmt;

        FlyCapture2::Property                prop;
        FlyCapture2::PropertyInfo            propInfo;

        void PrintError( FlyCapture2::Error error ){
            printf( "%s\n", error.GetDescription() );
        }

};



}
#endif

