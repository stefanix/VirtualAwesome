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


#include <vaOpencv/Image.h>


using namespace vaOpencv;


Image::Image( int w, int h, int depth, int channels ) {
	
    if ( ! (depth == IPL_DEPTH_8U || depth == IPL_DEPTH_16U || depth == IPL_DEPTH_32F) ){
        osg::notify(osg::WARN) << "in Image(), invalid depth format" << std::endl;
    }

    if ( ! (channels == 1 || channels == 3 || channels == 4) ){
        osg::notify(osg::WARN) << "in Image(), invalid channel number" << std::endl;
    }
        
    _width = w;
    _height = h;
    _iplDepth = depth;       // IPL_DEPTH_8U, IPL_DEPTH_16U, IPL_DEPTH_32F
    _channels = channels;  // 1, 3, 4
    
    // map ipl depth to gl depth
    // IPL_DEPTH_8U, IPL_DEPTH_16U, IPL_DEPTH_32F
    // --> GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, GL_FLOAT
    if (_iplDepth == IPL_DEPTH_8U) {
        _glDepth = GL_UNSIGNED_BYTE;
    } else if (_iplDepth == IPL_DEPTH_16U) {
        _glDepth = GL_UNSIGNED_SHORT;
    } else if (_iplDepth == IPL_DEPTH_32F) {
        _glDepth = GL_FLOAT;
    }

    // map channel number to gl channels
    // 1, 3, 4  -->  GL_LUMINANCE, GL_BGR, GL_BGRA
    if (_channels == 1) {
        _glChannels = GL_LUMINANCE;
    } else if (_channels == 3) {
        _glChannels = GL_BGR;
    } else if (_channels == 4) {
        _glChannels = GL_BGRA;
    }
        
    // allocate
    _cvImage = cvCreateImage( cvSize(_width,_height), _iplDepth, _channels );
    _cvImageTemp = cvCreateImage( cvSize(_width,_height), _iplDepth, _channels );
    _osgImage = new osg::Image();
    _osgImage->setImage( _width, _height, _channels, 
    	                _glChannels, _glChannels, _glDepth, 
                        (unsigned char*)_cvImage->imageData,
                        osg::Image::NO_DELETE, 1 );
}

Image::~Image() {
    cvReleaseImage( &_cvImage );
    cvReleaseImage( &_cvImageTemp );
}


void Image::swapTemp() {
	IplImage*  temp;
	temp = _cvImage;
	_cvImage	= _cvImageTemp;
	_cvImageTemp	= temp;
}


void Image::copyFrom( Image* mom ){
	if( mom->getWidth() == _width && 
    	mom->getHeight() == _height &&
	    mom->getChannels() == _channels && 
        mom->getDepth() == _iplDepth )
    {
    	cvCopy( mom->getIplImage(), _cvImage );
        dirty();
	} else {
        osg::notify(osg::FATAL) 
        	<< "in =, images need to match in size, channels, and depth" 
            << std::endl;
	}
}

void Image::copyFrom( IplImage* mom ) {
	if( mom->width == _width && 
    	mom->height == _height &&
	    mom->nChannels == _channels && 
        mom->depth == _iplDepth )
    {
		cvCopy( mom, _cvImage );
        dirty();
        osg::notify(osg::FATAL) << "assigning" << std::endl;
	} else {
        osg::notify(osg::FATAL) 
        	<< "in =, images need to match in size, channels, and depth" 
            << std::endl;
	}
}


void Image::set( double luminance ) {
	cvSet(_cvImage, cvScalar(luminance));
    dirty();
}
void Image::set( double r, double g, double b ){
	cvSet(_cvImage, cvScalar(r,g,b));
    dirty();
}

        
void Image::flip( bool bFlipHorizontally, bool bFlipVertically ) {
	int flipMode = 0;

	if( bFlipVertically && !bFlipHorizontally ) flipMode = 0;
	else if( !bFlipVertically && bFlipHorizontally ) flipMode = 1;
	else if( bFlipVertically && bFlipHorizontally ) flipMode = -1;
	else return;

	cvFlip( _cvImage, _cvImageTemp, flipMode );
	swapTemp();
    dirty();
}


void Image::remap( IplImage* mapX, IplImage* mapY ){
    cvRemap( _cvImage, _cvImageTemp, mapX, mapY );
	swapTemp();
    dirty();
}



void Image::dirty() {
    // rewrap _cvImage pixels width the osg::Image, does not copy
    // s, t, r, internalTextureformat, pixelFormat, type, data, mode, packing
    _osgImage->setImage( _width, _height, _channels, 
    	_glChannels, _glChannels, _glDepth, 
        (unsigned char*)_cvImage->imageData, 
        osg::Image::NO_DELETE, 1 );    
    _osgImage->dirty();
}

