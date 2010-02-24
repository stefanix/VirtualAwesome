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

#include <vaTouchkit/Tracker.h>


using namespace vaTouchkit;


Tracker::Tracker( int w, int h ){
	_width = w;
	_height = h;
    _targetWidth = w;
    _targetHeight = h;
    _bNewFrame = false;
	_bSetupMode = true;
    _bPlay = true;
    _camFrameCount = 0;
    _camFps = 0;
    _dspTime = 0;
    setName("Tracker");
    
    //get screen _targetWidth, _targetHeight
    osg::GraphicsContext::WindowingSystemInterface* wsi = osg::GraphicsContext::getWindowingSystemInterface();
    if (!wsi) {
        osg::notify(osg::FATAL)<<"no WindowSystemInterface available"<<std::endl;
    }
    wsi->getScreenResolution(osg::GraphicsContext::ScreenIdentifier(0), _targetWidth, _targetHeight);    
    
    
    disableLighting();
    disableDepthTest();
    enableUpdateCallback();
    
    _videoGrabber = NULL;
    _jpegGrabber = NULL;
    
    _image = new vaOpencv::Image(_width, _height, IPL_DEPTH_8U, 1);
    
    _setupPanel = new va::PanelWidget(2.3*_width,480);
    _setupPanel->setName("Setup Panel");
    _setupPanel->setLabel("Setup Panel");
    _setupPanel->setBackgroundColor(0.0f, 0.0f, 0.0f, 0.3f);
    _setupPanel->disableTouchEvents();
    addChild(_setupPanel);    
    
    _afterAcquiringImg = new vaOpencv::Image(_width, _height, IPL_DEPTH_8U, 1);
    _afterAcquiringImgShape = new va::ImageShape();
    _afterAcquiringImgShape->setImage(_afterAcquiringImg->getOsgImage());
    _afterAcquiringImgShape->setPosition(0.1*_width, 160, 0);
    _setupPanel->addChild(_afterAcquiringImgShape);

    _visionMap = new VisionMap(_width, _height);
    _visionMap->setPosition(0.1*_width, 160, 0);
    _setupPanel->addChild(_visionMap);

	_filter = new AdaptiveFilter(_width, _height);
    _filter->setThreshold(30);
    _filter->setAccumulationFactor(0.001);
    
    _afterFilteringImg = new vaOpencv::Image(_width, _height, IPL_DEPTH_8U, 1);
    _afterFilteringImgShape = new va::ImageShape();
    _afterFilteringImgShape->setImage(_afterFilteringImg->getOsgImage());
    _afterFilteringImgShape->setPosition(1.2*_width, 160, 0);
    _setupPanel->addChild(_afterFilteringImgShape);
    
    _contourFinder = new ContourFinder(_width, _height);
    
    _blobTracker = new BlobTracker(_width, _height, _visionMap);
    _blobTracker->setScale(_targetWidth/(float)_width, _targetHeight/(float)_height);
    
    
    //add some widgtes
    //
    va::ButtonWidget* pauseButton = new va::ButtonWidget(160,30);
    pauseButton->setName("Toggle");
    pauseButton->setLabel("Pause Tracking");
    pauseButton->setPivot(80, 15, 0);    
    pauseButton->setPosition(0.6*_width, 100, 0);
    pauseButton->addEventHandler(this);
    _setupPanel->addChild(pauseButton);

    va::ButtonWidget* resetButton = new va::ButtonWidget(160,30);
    resetButton->setName("Reset");
    resetButton->setLabel("Reset Background");
    resetButton->setPivot(80, 15, 0);
    resetButton->setPosition(0.6*_width, 50, 0);
    resetButton->addEventHandler(this);
    _setupPanel->addChild(resetButton);
    
    va::TextShape* blurb = new va::TextShape(_width, 80);
    blurb->setPosition(1.2*_width,30,0);
    blurb->appendText("Press [s] to toggle setup panel.");
    _setupPanel->addChild(blurb);
}



Tracker::~Tracker(){
	if (_videoGrabber != NULL) {
        delete _videoGrabber;
    }

	if (_jpegGrabber != NULL) {
        delete _jpegGrabber;
    }
    
    delete _image;
    delete _afterAcquiringImg;
    
    delete _contourFinder;
    delete _blobTracker;
    
}



void Tracker::setTargetResolution( int w, int h ){
	_targetWidth = w;
    _targetHeight = h;
}

void Tracker::addEventHandler( va::RawTouchHandler* handler ){
    _blobTracker->addEventHandler(handler);
}


void Tracker::setSetupMode(bool bSetup){
	_bSetupMode = bSetup;
    _setupPanel->setVisible(_bSetupMode);
}


void Tracker::listDevices(){
	if (_videoGrabber == NULL) {
        _videoGrabber = new VideoGrabber(_width, _height);
    }
	_videoGrabber->listDevices();
}

bool Tracker::selectDevice( int index ){
	if (_videoGrabber == NULL) {
        _videoGrabber = new VideoGrabber(_width, _height);
    }
	return _videoGrabber->selectDevice(index);
}
/*
bool Tracker::selectDeviceByGuid( unsigned long long guid ){
	if (_videoGrabber == NULL) {
        _videoGrabber = new VideoGrabber(_width, _height);
    }
	return _videoGrabber->selectDeviceByGuid(guid);
}
*/

bool Tracker::selectJpegs( const std::string& fistJpeg, int numDigits, int start, int end ) {
	if (_jpegGrabber == NULL) {
        _jpegGrabber = new JpegGrabber(_width, _height);
    }
    return _jpegGrabber->selectJpegs(fistJpeg, numDigits, start, end);
}


void Tracker::update(){
	bool _bNewFrame = false;
    
    if (_bPlay) {
        if (_videoGrabber != NULL) {
            _videoGrabber->grabFrameInto(_image->getOsgImage());
            _bNewFrame = _videoGrabber->isFrameNew();
        } else if (_jpegGrabber != NULL) {
            _jpegGrabber->grabFrameInto(_image->getOsgImage());
            _bNewFrame = _jpegGrabber->isFrameNew();
        }
    }

    if (_bNewFrame) {
        if (_bSetupMode) {                    	
            if( (_camFrameCount % 60) == 0 ) {                
                _camFps = 60/_camFrameTimer.time_s();
                _camFrameTimer.setStartTick();
            }
            _dspTimer.setStartTick();
        }
        
        
		//_image->flip(true, false);
        if( true ) { _afterAcquiringImg->copyFrom(_image); }
        
		_filter->apply(_image);                
        if( _bSetupMode ) { _afterFilteringImg->copyFrom(_image); }
        
        //findContures( img, minSize, maxSize, nMax, inner contours yes/no )
        _contourFinder->find(_image, 5,400, 10, false );
                
        _blobTracker->track(_contourFinder);
        
        
        if( _bSetupMode ) {
            _dspTime = _dspTimer.time_m();
            _camFrameCount++;
        }
        
    }    
    
}


void Tracker::widget( va::ButtonWidget& button ) {
	if (button.getName() == "Toggle") {
    	if( getPlay() ) {
            setPlay( false );
            button.setLabel("Run Tracking");
        } else {
            setPlay( true );
            button.setLabel("Pause Tracking");
        }
    } else if (button.getName() == "Reset") {
        resetBackground();
    }
}
void Tracker::widget( va::SliderWidget& slider ){}
void Tracker::widget( va::ToggleWidget& toggle ){}

