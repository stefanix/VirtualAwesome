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

#ifndef VATOUCHKIT_CONTOUR_FINDER
#define VATOUCHKIT_CONTOUR_FINDER


#include <vector>
#include <cv.h>
#include <vaOpencv/Image.h>
#include <va/Constants.h>
#include <vaTouchkit/Contour.h>


namespace vaTouchkit {

static const int MAX_CONTOURS = 128;


class ContourFinder {
    public:
        
		std::vector<Contour> contours;
        
        ContourFinder( int w, int h );
        ~ContourFinder();
        
        void find( vaOpencv::Image* image,
                   int minArea,
                   int maxArea,
                   int nConsidered,
                   bool bFindHoles );

    protected:

    	int _width;
    	int _height;
        IplImage*  _inputCopy;
        CvMemStorage*  contour_storage;
        CvMemStorage*  storage;
        CvMoments*  myMoments;

        int nCvSeqsFound;
        CvSeq*  cvSeqBlobs[MAX_CONTOURS]; 
    
};



}
#endif

