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

#include <vaTouchkit/AdaptiveFilter.h>


using namespace vaTouchkit;



AdaptiveFilter::AdaptiveFilter( int w, int h ){
	_width = w;
    _height= h;
	_bResetBg = true;
    _f = 0.001;
    _threshold = 30;
    _shortImageTemp = cvCreateImage( cvSize(_width,_height), IPL_DEPTH_16U, 1);
    _accumImage = cvCreateImage( cvSize(_width,_height), IPL_DEPTH_16U, 1);
    _byteImageTemp = cvCreateImage( cvSize(_width,_height), IPL_DEPTH_8U, 1);
}



AdaptiveFilter::~AdaptiveFilter(){
    cvReleaseImage( &_shortImageTemp );
    cvReleaseImage( &_accumImage );
    cvReleaseImage( &_byteImageTemp );
}

void AdaptiveFilter::apply( vaOpencv::Image* image ){
    if( _bResetBg ) {
        cvConvertScale( image->getIplImage(), _accumImage, 65535.0f/255.0f, 0 );
        _bResetBg = false;
    } else {
        cvConvertScale( image->getIplImage(), _shortImageTemp, 65535.0f/255.0f, 0 );
        cvAddWeighted( _shortImageTemp, _f, _accumImage, 1.0f-_f,0, _accumImage );
    }
    
    cvConvertScale(_accumImage, _byteImageTemp, 255.0f/65535.0f, 0);

    // get lighter spots
    cvSub(image->getIplImage(), _byteImageTemp, image->getIplImage());
    
    cvThreshold(image->getIplImage(), image->getIplImage(), _threshold, 255, CV_THRESH_BINARY);

	// get rid of noise
    cvErode(image->getIplImage(), image->getIplImage());
    cvDilate(image->getIplImage(), image->getIplImage());
}

