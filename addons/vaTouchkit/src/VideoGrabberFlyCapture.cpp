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
* This file implements the VideoGrabber for Windows.
*
*/

#include <va/Constants.h>

#if defined( TARGET_WIN32 )


#include <vaTouchkit/VideoGrabberFlyCapture.h>


using namespace vaTouchkit;



VideoGrabber::VideoGrabber( int w, int h ){
	_width = w;
	_height = h;
    _depth = 1;
    _bGrabberReady = false;
	_bIsFrameNew = false;

	k_fmt7Mode = FlyCapture2::MODE_1;  // 2x2 pixel binning
    k_fmt7PixFmt = FlyCapture2::PIXEL_FORMAT_MONO8;
	

    unsigned int numCameras;
    err = busMgr.GetNumOfCameras(&numCameras);
    if(err!=FlyCapture2::PGRERROR_OK){ 
        osg::notify(osg::WARN) << "Failed to enumerate cameras" << std::endl;
    }

    if( numCameras == 0 ) {
		osg::notify(osg::WARN) << "No cameras found" << std::endl;
    }
}


VideoGrabber::~VideoGrabber(){
    // Stop capturing images
    err = cam.StopCapture();
    if (err != FlyCapture2::PGRERROR_OK){
        PrintError( err );
        return;
    }      

    // Disconnect the camera
    err = cam.Disconnect();
    if (err != FlyCapture2::PGRERROR_OK){
        PrintError( err );
        return;
    }

}


void VideoGrabber::listDevices(){
    osg::notify(osg::ALWAYS) << "-------------------------------------" << std::endl;
        
	//ofLog(OF_LOG_NOTICE, "Listing available IIDC capture devices.\nUse unit number as unique ID for camera...");
	//for (uint32_t index = 0; index < deviceList->num; index++) {
	//	//printf("Using camera with GUID %"PRIx64"\n", camera->guid);
	//	ofLog(OF_LOG_NOTICE, "Device[%d].unit = %x, GUID = %x", index, deviceList->ids[index].unit, deviceList->ids[index].guid);
	//}    
    
    osg::notify(osg::ALWAYS) << "-------------------------------------" << std::endl;
}


bool VideoGrabber::selectDevice( int index ){	

    //-----------------------------------------------------------------------
    // select camera
    //-----------------------------------------------------------------------
    err = busMgr.GetCameraFromIndex(index, &guid);
    if (err != FlyCapture2::PGRERROR_OK){
        PrintError( err );
        return false;
    }

    // Connect to a camera
    err = cam.Connect(&guid);
    if (err != FlyCapture2::PGRERROR_OK){
        PrintError( err );
        return false;
    }


    //-----------------------------------------------------------------------
    // set features
    //-----------------------------------------------------------------------
    // Set the brighness property of the camera
    prop.type = FlyCapture2::BRIGHTNESS;
    err = cam.GetProperty( &prop );
    if (err != FlyCapture2::PGRERROR_OK){
        PrintError( err );
        return false;
    }

    prop.autoManualMode = false;
    prop.valueA = 120;  //1-255

    err = cam.SetProperty( &prop );
    if (err != FlyCapture2::PGRERROR_OK){
        PrintError( err );
        return false;
    }

    // exposure
    prop.type = FlyCapture2::AUTO_EXPOSURE;
    err = cam.GetProperty( &prop );
    if (err != FlyCapture2::PGRERROR_OK){
        PrintError( err );
        return false;
    }

    prop.autoManualMode = false;
    prop.valueA = 50;  //7-62

    err = cam.SetProperty( &prop );
    if (err != FlyCapture2::PGRERROR_OK){
        PrintError( err );
        return false;
    }


    // gain
    prop.type = FlyCapture2::GAIN;
    err = cam.GetProperty( &prop );
    if (err != FlyCapture2::PGRERROR_OK){
        PrintError( err );
        return false;
    }

    prop.autoManualMode = false;
    prop.valueA = 64;  //16-64

    err = cam.SetProperty( &prop );
    if (err != FlyCapture2::PGRERROR_OK){
        PrintError( err );
        return false;
    }
    
    // shutter
    prop.type = FlyCapture2::SHUTTER;
    err = cam.GetProperty( &prop );
    if (err != FlyCapture2::PGRERROR_OK){
        PrintError( err );
        return false;
    }

    prop.autoManualMode = false;
    prop.valueA = 500;  //1-524

    err = cam.SetProperty( &prop );
    if (err != FlyCapture2::PGRERROR_OK){
        PrintError( err );
        return false;
    }


    // pan
    prop.type = FlyCapture2::PAN;
    err = cam.GetProperty( &prop );
    if (err != FlyCapture2::PGRERROR_OK){
        PrintError( err );
        return false;
    }

    prop.autoManualMode = false;
    prop.valueA = 80;  //0-112

    err = cam.SetProperty( &prop );
    if (err != FlyCapture2::PGRERROR_OK){
        PrintError( err );
        return false;
    }


    //-----------------------------------------------------------------------
    // get  camera info
    //-----------------------------------------------------------------------
    // Get the camera information
    err = cam.GetCameraInfo(&camInfo);
    if (err != FlyCapture2::PGRERROR_OK){
        PrintError( err );
        return false;
    }

    //PrintCameraInfo(&camInfo);

    // Get EXPOSURE Property
    propInfo.type = FlyCapture2::PAN;
    err = cam.GetPropertyInfo( &propInfo );
    if (err != FlyCapture2::PGRERROR_OK){
        PrintError( err );
        return false;
    }
    std::cout << "----EXPOSURE---------" << std::endl;
    std::cout << "min " << propInfo.min << std::endl;
    std::cout << "max " << propInfo.max << std::endl;
    std::cout << "absMin " << propInfo.absMin << std::endl;
    std::cout << "absMax " << propInfo.absMax << std::endl;

    prop.type = FlyCapture2::PAN;
    err = cam.GetProperty( &prop );
    if (err != FlyCapture2::PGRERROR_OK){
        PrintError( err );
        return false;
    }
    std::cout << "valueA " << prop.valueA << std::endl;
    std::cout << "valueB " << prop.valueA << std::endl;


    //-----------------------------------------------------------------------
    // setup capture
    //-----------------------------------------------------------------------
    // Query for available Format 7 modes
    bool supported;
    fmt7Info.mode = k_fmt7Mode;
    err = cam.GetFormat7Info( &fmt7Info, &supported );
    if (err != FlyCapture2::PGRERROR_OK){
        PrintError( err );
        return false;
    }

    //PrintFormat7Capabilities( fmt7Info );

    if ( (k_fmt7PixFmt & fmt7Info.pixelFormatBitField) == 0 ){
        // Pixel format not supported!
		printf("Pixel format is not supported\n");
        return false;
    }
    
    fmt7ImageSettings.mode = k_fmt7Mode;
    fmt7ImageSettings.offsetX = 0;
    fmt7ImageSettings.offsetY = 0;
    //fmt7ImageSettings.width = fmt7Info.maxWidth;
    //fmt7ImageSettings.height = fmt7Info.maxHeight;
    fmt7ImageSettings.width = _width;
    fmt7ImageSettings.height = _height;
    fmt7ImageSettings.pixelFormat = k_fmt7PixFmt;

    // Validate the settings to make sure that they are valid
    bool valid;
    err = cam.ValidateFormat7Settings(
        &fmt7ImageSettings,
        &valid,
        &fmt7PacketInfo );
    if (err != FlyCapture2::PGRERROR_OK){
        PrintError( err );
        return false;
    }

    if ( !valid ){
		printf("Format7 settings are not valid\n");
        return false;
    }

    // Set the settings to the camera
    err = cam.SetFormat7Configuration(
        &fmt7ImageSettings,
        fmt7PacketInfo.recommendedBytesPerPacket );
    if (err != FlyCapture2::PGRERROR_OK){
        PrintError( err );
        return false;
    }


    //-----------------------------------------------------------------------
    // have the camera start sending us data
    //-----------------------------------------------------------------------
    err = cam.StartCapture();
    if (err != FlyCapture2::PGRERROR_OK){
        PrintError( err );
        return false;
    }

    // Retrieve frame rate property
    frmRate.type = FlyCapture2::FRAME_RATE;
    err = cam.GetProperty( &frmRate );
    if (err != FlyCapture2::PGRERROR_OK){
        PrintError( err );
        return false;
    }

    printf( "Frame rate is %3.2f fps\n", frmRate.absValue );
    return true;
}



bool  VideoGrabber::isFrameNew(){
	return _bIsFrameNew;
}



void VideoGrabber::grabFrameInto( osg::Image* image ){

    // Retrieve an image
    err = cam.RetrieveBuffer( &rawImage );
    if (err != FlyCapture2::PGRERROR_OK){
        PrintError( err );
        return;
    }
    
    _bIsFrameNew = true;

    // copy into pixels
    if( (unsigned int)_width == rawImage.GetStride() && (unsigned int)_width == image->getRowSizeInBytes() ) {
        memcpy( image->data(), rawImage.GetData(), _width*_height );
    } else {
        // watch for row alignment
        for( int i = 0; i < _height; i++ ) {
            memcpy( image->data() + (i*image->getRowSizeInBytes()), 
                    rawImage.GetData() + (i*rawImage.GetStride()), 
                    _width );
        }
    }

}





#endif


