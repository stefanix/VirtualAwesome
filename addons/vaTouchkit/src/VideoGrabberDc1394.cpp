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
* This file implements the VideoGrabber for OSX and Linux.
*
*/

#include <va/Constants.h>

#if defined( TARGET_OSX ) || defined( TARGET_LINUX )


#include <vaTouchkit/VideoGrabberDc1394.h>


using namespace vaTouchkit;



VideoGrabber::VideoGrabber( int w, int h ){
	_width = w;
	_height = h;
    _depth = 1;
    _bGrabberReady = false;
	_bIsFrameNew = false;

	frame = NULL;
	driver = NULL;
	deviceList = NULL;
	camera = NULL;
	color_coding = DC1394_COLOR_CODING_MONO8;
	framerate = DC1394_FRAMERATE_60;

	if(_width == 320 && _height == 240) {
		video_mode = DC1394_VIDEO_MODE_FORMAT7_1;  //2x2 pixel binning
	} else {
		video_mode = DC1394_VIDEO_MODE_FORMAT7_0;
	}
	
	
	
    driver = dc1394_new();
    if (!driver) { return; }
    err = dc1394_camera_enumerate(driver, &deviceList);
	if(err){ osg::notify(osg::FATAL)<<"Failed to enumerate cameras"<<std::endl; }

    if( deviceList->num == 0 ) {
        osg::notify(osg::FATAL)<<"No cameras found"<<std::endl;
    }
}



VideoGrabber::~VideoGrabber(){
    if (camera != NULL) {
        dc1394_video_set_transmission(camera, DC1394_OFF);
        dc1394_capture_stop(camera);
        dc1394_camera_free(camera);
    }

    //free device enumeration
    dc1394_camera_free_list(deviceList);

    //free context
    dc1394_free(driver);

}


void VideoGrabber::listDevices(){
    osg::notify(osg::NOTICE)<<"-------------------------------------"<<std::endl;
    osg::notify(osg::NOTICE)<<"Listing available IIDC capture devices."<<std::endl
                            <<"Use unit number as unique ID for camera..."<<std::endl;
	for (uint32_t index = 0; index < deviceList->num; index++) {
        osg::notify(osg::NOTICE)<<"Device["<<index<<"].unit = "
                                <<deviceList->ids[index].unit
                                <<", GUID = "
                                <<deviceList->ids[index].guid<<"LLU"
                                <<std::endl;
	}
    osg::notify(osg::NOTICE)<<"-------------------------------------"<<std::endl;
}


bool VideoGrabber::selectDeviceByGuid( uint64_t guid ){
    if( deviceList->num > 0 ) {
		int index = 0;
        bool bFound = false;
        for (uint32_t i=0; i<deviceList->num; i++) {
            if (deviceList->ids[index].guid == guid) {
                bFound = true;
				index = i;
            }
        }
        if (!bFound) {
        	osg::notify(osg::NOTICE)<<"in selectDeviceByGuid, device ["
				<<guid<<"] not found, using first device"<<std::endl;
        }
		return selectDevice(index);
    } else {
        osg::notify(osg::FATAL)<<"in selectDeviceByGuid, no devices found"<<std::endl;
        return false;
    }
}
	
bool VideoGrabber::selectDevice( int index ){
	// In format_7 the framerate is set by setting the packet_size
	// this is used in dc1394_format7_set_roi()
	// The following formula is from the libdc1394 faq
	// http://damien.douxchamps.net/ieee1394/libdc1394/v2.x/faq/#How_can_I_work_out_the_packet_size_for_a_wanted_frame_rate
	//float bus_period = 0.000125;  // for firewire 400
	//int frame_rate = 60;
	//int num_packets = (int)(1.0/(bus_period*frame_rate) + 0.5);
	//packet_size =  (_width*_height*depth + (num_packets*8) - 1)/(num_packets*8);
	packet_size = DC1394_USE_MAX_AVAIL;	

    //first choose a device to use
    if( ((unsigned int)index >= deviceList->num) || (index < 0) ) {
        osg::notify(osg::FATAL)<<"in selectDevice, device not found"<<std::endl;
        return false;
    }

	uint64_t deviceGuid = deviceList->ids[index].guid;
    camera = dc1394_camera_new(driver, deviceGuid);
	if (!camera) {
        osg::notify(osg::FATAL)<<"Failed to initialize camera with guid "<<deviceGuid<<std::endl;
		return false;
	}

    /*-----------------------------------------------------------------------
     *  setup capture
     *-----------------------------------------------------------------------*/

    err = dc1394_video_set_iso_speed(camera, DC1394_ISO_SPEED_400);
    if( err != DC1394_SUCCESS ) { osg::notify(osg::FATAL)<<"failed to set iso speed"<<std::endl; return false; }
	
	err = dc1394_video_set_mode( camera, video_mode );
	if( err != DC1394_SUCCESS ) { osg::notify(osg::FATAL)<<"failed to set format 7 video mode"<<std::endl; return false; }
	
	err = dc1394_format7_set_color_coding(camera, video_mode, color_coding);
	if( err != DC1394_SUCCESS ) { osg::notify(osg::FATAL)<<"failed to set format 7 color coding"<<std::endl; return false; }
	
	err = dc1394_format7_set_packet_size(camera, video_mode, packet_size);
	if( err != DC1394_SUCCESS ) { osg::notify(osg::FATAL)<<"failed to set format 7 packet_size"<<std::endl; return false; }
	
	err = dc1394_format7_set_roi(camera, video_mode, color_coding, packet_size, 0,0, _width,_height);
	if( err != DC1394_SUCCESS ) { osg::notify(osg::FATAL)<<"failed to set format 7"<<std::endl; return false; }

    //err = dc1394_video_set_framerate(camera, framerate);
	//DC1394_ERR_CLN_RTN(err,cleanup_and_exit(camera),"Could not set framerate");

    err = dc1394_capture_setup(camera,2, DC1394_CAPTURE_FLAGS_DEFAULT);
	if( err != DC1394_SUCCESS ) { osg::notify(osg::FATAL)<<"failed to setup dma capturing"<<std::endl; return false; }


	/*-----------------------------------------------------------------------
     *  set camera's features
     *-----------------------------------------------------------------------*/

	err = dc1394_feature_set_mode(camera, DC1394_FEATURE_BRIGHTNESS, DC1394_FEATURE_MODE_MANUAL);
	err = dc1394_feature_set_value(camera, DC1394_FEATURE_BRIGHTNESS, 200);  //1-255

	err = dc1394_feature_set_mode(camera, DC1394_FEATURE_EXPOSURE, DC1394_FEATURE_MODE_MANUAL);
	err = dc1394_feature_set_value(camera, DC1394_FEATURE_EXPOSURE, 62);  //7-62

	err = dc1394_feature_set_mode(camera, DC1394_FEATURE_SHUTTER, DC1394_FEATURE_MODE_MANUAL);
	err = dc1394_feature_set_value(camera, DC1394_FEATURE_SHUTTER, 60);  //1-263, 64 being the max for 60fps

	err = dc1394_feature_set_mode(camera, DC1394_FEATURE_GAIN, DC1394_FEATURE_MODE_MANUAL);
	err = dc1394_feature_set_value(camera, DC1394_FEATURE_GAIN, 50);  //16-64

	//err = dc1394_feature_set_mode(camera, DC1394_FEATURE_PAN, DC1394_FEATURE_MODE_MANUAL);
	//err = dc1394_feature_set_value(camera, DC1394_FEATURE_PAN, 56);


    /*-----------------------------------------------------------------------
     *  report camera's features
     *-----------------------------------------------------------------------*/
    err=dc1394_feature_get_all(camera,&features);
    if (err!=DC1394_SUCCESS) {
        dc1394_log_warning("Could not get feature set");
        return false; 
    } else {
        dc1394_feature_print_all(&features, stdout);
    }

    /*-----------------------------------------------------------------------
     *  have the camera start sending us data
     *-----------------------------------------------------------------------*/
    err=dc1394_video_set_transmission(camera, DC1394_ON);
    //DC1394_ERR_CLN_RTN(err,cleanup_and_exit(camera),"Could not start camera iso transmission");
    
    _bGrabberReady = true;
    return true;  
}





bool  VideoGrabber::isFrameNew(){
	return _bIsFrameNew;
}


void VideoGrabber::grabFrameInto( osg::Image* image ){
    if (camera != NULL) {
		// get a frame
        // The first time you call a DMA capture function dc1394_capture_dequeue() it returns
		// a pointer to the first frame buffer structure (dc1394frame_t). After a successful
		// capture function call, the capture_buffer pointer and the frame buffer it points
		// to are available to you for reading and writing. It will not be overwritten with
		// a newer frame while it is allocated to you (FREE), even if the ring buffer overflows.
		// Once you have finished with it you should release it as soon as possible with a call
		// to dc1394_capture_enqueue().
		err = dc1394_capture_dequeue(camera, DC1394_CAPTURE_POLICY_POLL, &frame);
        if (frame == NULL) {
            _bIsFrameNew = false;
        } else {
			_bIsFrameNew = true;

			// copy into pixels
			if( (unsigned int)_width == frame->stride && (unsigned int)_width == image->getRowSizeInBytes() ) {
			    memcpy( image->data(), frame->image, _width*_height );
			} else {
			    // watch for row alignment
    			for( int i = 0; i < _height; i++ ) {
    				memcpy( image->data() + (i*image->getRowSizeInBytes()), 
                            frame->image + (i*frame->stride), 
                            _width );
    			}
            }

			// make frame available again as part of the
			// ring buffer receiving images from the cam
			err = dc1394_capture_enqueue(camera, frame);
		}
	}
}


#endif





