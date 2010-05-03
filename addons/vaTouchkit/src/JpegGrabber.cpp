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

#include <vaTouchkit/JpegGrabber.h>


using namespace vaTouchkit;



JpegGrabber::JpegGrabber( int w, int h ){
	_width = w;
	_height = h;
    _depth = 1;
    _bGrabberReady = false;
	_bIsFrameNew = false;
    _frameCounter = 0;
}



JpegGrabber::~JpegGrabber(){
//	for(int i=0; i<_sequence.size(); i++) {
//    	delete _sequence[i];
//    }
}


bool JpegGrabber::selectJpegs( const std::string& fistJpeg, int numDigits, int start, int end  ){

	std::string suffix = ".jpg";
    std::string jpegroot = fistJpeg.substr(0,fistJpeg.size()-suffix.size()-numDigits);
    std::ostringstream indexString;

    for(int i=start; i<end; i++) {
        indexString.str("");  //reset
    	indexString << std::setw(numDigits) << std::setfill('0') << i;
        std::string filename = jpegroot + indexString.str() + suffix;

        osg::ref_ptr<osg::Image> image= osgDB::readImageFile(filename);

        if (image.valid()) {
        	/*if ( !(image->getPixelFormat() == GL_RGBA || image->getPixelFormat() == GL_LUMINANCE)
                 || !(image->getDataType() == GL_UNSIGNED_BYTE)
                 || !(image->getPacking() == 1) )
            {
                osg::notify(osg::WARN)<<"jpeg came in the wrong format, this should not happen"<<std::endl;
                std::cout << "s:" << image->s() << " | "
                	<< "t:" << image->t() << " | "
                	<< "r:" << image->r() << " | "
                	<< "getInternalTextureFormat:" << image->getInternalTextureFormat() << "[" << GL_LUMINANCE << "] | "
                	<< "getPixelFormat:" << image->getPixelFormat() << "[" << GL_LUMINANCE << "] | "
                	<< "getDataType:" << image->getDataType() << "[" << GL_UNSIGNED_BYTE << "] | "
                	<< "getPacking:" << image->getPacking() << " | "
                	<< std::endl;
                //return false;
            }*/

			if (image->s() != _width || image->t() != _height) {
                image->scaleImage(_width, _height, 1, GL_LUMINANCE);
            }


            // convert color space
            // on different OSes jpegs come in differently no matter how they are stored
            if (image->getPixelFormat() == GL_RGBA || image->getPixelFormat() == GL_RGB) {
                int nChannelStep = 3;
                if (image->getPixelFormat() == GL_RGBA){
                    nChannelStep = 4;
                }
            	osg::notify(osg::INFO)<<"converting jpeg to grayscale ..."<<std::endl;
                osg::ref_ptr<osg::Image> imageGray = new osg::Image();
                imageGray->allocateImage(_width, _height, _depth, GL_LUMINANCE, GL_UNSIGNED_BYTE, 1);

                int gray = 0;
                int r = 0;
                int g = 0;
                int b = 0;
                for(int i=0; i<_height; i++) {
                    for(int j=0; j<_width; j++) {
                    	gray = 0;
                        r = *(image->data() + i*nChannelStep*_width + nChannelStep*j + 0);
                        g = *(image->data() + i*nChannelStep*_width + nChannelStep*j + 1);
                        r = *(image->data() + i*nChannelStep*_width + nChannelStep*j + 2);
                        gray = 0.3*r + 0.59*g + 0.11*b;
                        *(imageGray->data() + i*_width + j) = gray;
                    }
                }

                // push it into the sequence
                _sequence.push_back(imageGray);
            } else {
            	// push it into the sequence
                _sequence.push_back(image);
            }
        } else {
        	osg::notify(osg::WARN)<<"failed load jpeg sequence"<<std::endl;
            return false;
        }
    }

    _bGrabberReady = true;
    return true;
}




bool  JpegGrabber::isFrameNew(){
	return _bIsFrameNew;
}


void JpegGrabber::grabFrameInto( osg::Image* image ){
    if (_bGrabberReady && _sequence.size() > 0) {
        _bIsFrameNew = true;

        unsigned int currentFrame = _frameCounter % _sequence.size();
        _frameCounter++;

		// assume same image specs, TODO some checks
        memcpy( image->data(), _sequence[currentFrame]->data(), _width*_height );

        image->dirty();
	}
}

