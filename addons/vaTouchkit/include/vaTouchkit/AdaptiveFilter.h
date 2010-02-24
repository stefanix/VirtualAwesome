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

#ifndef VATOUCHKIT_ADAPTIVE_FILTER
#define VATOUCHKIT_ADAPTIVE_FILTER


#include <cv.h>
#include <vaOpencv/Image.h>
#include <va/Constants.h>


namespace vaTouchkit {


class AdaptiveFilter {

	public :
		
		AdaptiveFilter(int w, int h);
		virtual ~AdaptiveFilter();
        
        void setThreshold( int value ) {_threshold=value;}
        void setAccumulationFactor( float value ) {_f = value;}
        void resetBackground() {_bResetBg = true;}
		virtual void apply( vaOpencv::Image* image );
        
        	
	protected:
    
    	int _width;
    	int _height;
    	bool _bResetBg;
        float _f;
        int _threshold;
        IplImage* _shortImageTemp;
        IplImage* _accumImage;
        IplImage* _byteImageTemp;
                
};



}
#endif

