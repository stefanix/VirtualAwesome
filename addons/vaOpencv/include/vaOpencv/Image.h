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
* vaOpencv::Image wraps OpenCV functions 
*
* A color IplImage is BGR or BGRA, channels are interleaved
*/


#ifndef SXOPENCV_IMAGE
#define SXOPENCV_IMAGE


#include <cv.h>

#include <osg/Notify>
#include <osg/Image>
#include <osgDB/ReaderWriter>


namespace vaOpencv {


class Image {
    public:
  
        Image( int w, int h, int depth, int nChannels );
        // depth can be one of the following:
        // IPL_DEPTH_8U, IPL_DEPTH_16U, IPL_DEPTH_32F
        // nChannels can be either:
        // 1, 3, 4
        
        ~Image();
        
        int getWidth(){ return _width; }
        int getHeight(){ return _height; }
        int getDepth(){ return _iplDepth; }
        int getChannels(){ return _channels; }

        virtual void copyFrom( Image* mom );
        virtual void copyFrom( IplImage* mom );
        
        void set( double luminance );
        void set( double r, double g, double b );
        void flip( bool bFlipVertically, bool bFlipHorizontally );
        
        void remap( IplImage* mapX, IplImage* mapY );
        
        virtual void dirty();
        osg::Image* getOsgImage(){ return _osgImage; }
        IplImage* getIplImage(){ return _cvImage; }
    
    protected:
    	int _width;
        int _height;
        int _iplDepth;
        int _channels;
        int _glDepth;
        int _glChannels;
        
        IplImage*    _cvImage;
        IplImage*    _cvImageTemp;
        osg::ref_ptr<osg::Image>  _osgImage;
        
        virtual void swapTemp();  // swap cvImageTemp back
                                  // to cvImage after an image operation        
        
};


}
#endif

