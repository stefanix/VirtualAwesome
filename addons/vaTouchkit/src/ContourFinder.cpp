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

#include <vaTouchkit/ContourFinder.h>


using namespace vaTouchkit;



static int qsort_carea_compare( const void* _a, const void* _b) {
	int out = 0;
	// pointers, ugh.... sorry about this
	CvSeq* a = *((CvSeq **)_a);
	CvSeq* b = *((CvSeq **)_b);
	// use opencv to calc size, then sort based on size
	float areaa = fabs(cvContourArea(a, CV_WHOLE_SEQ));
	float areab = fabs(cvContourArea(b, CV_WHOLE_SEQ));
	// note, based on the -1 / 1 flip
	// we sort biggest to smallest, not smallest to biggest
	if( areaa > areab ) { out = -1; }
	else {                out =  1; }
	return out;
}





ContourFinder::ContourFinder( int w, int h ){
	_width = w;
    _height= h;
	myMoments = (CvMoments*)malloc( sizeof(CvMoments) );
	_inputCopy = cvCreateImage( cvSize(_width,_height), IPL_DEPTH_8U, 1);
}

ContourFinder::~ContourFinder() {
	free( myMoments );
    cvReleaseImage( &_inputCopy );
}
 


void ContourFinder::find( vaOpencv::Image* image,
                          int minArea,
                          int maxArea,
                          int nConsidered,
                          bool bFindHoles)
{
	contours.clear();

	// assumed that input image has same properties
	cvCopy(image->getIplImage(), _inputCopy);

	CvSeq* contour_list = NULL;
	contour_storage = cvCreateMemStorage( 1000 );
	storage	= cvCreateMemStorage( 1000 );

	CvContourRetrievalMode  retrieve_mode 
        = (bFindHoles) ? CV_RETR_LIST : CV_RETR_EXTERNAL;
	cvFindContours( _inputCopy, contour_storage, &contour_list, 
                    sizeof(CvContour), retrieve_mode, CV_CHAIN_APPROX_SIMPLE );
	CvSeq* contour_ptr = contour_list;
		
	nCvSeqsFound = 0;


	// put the contours from the linked list, into an array for sorting
	while( (contour_ptr != NULL) ) {
		float area = fabs( cvContourArea(contour_ptr, CV_WHOLE_SEQ) );
		if( (area > minArea) && (area < maxArea) ) {
            if( nCvSeqsFound < MAX_CONTOURS ) {
                cvSeqBlobs[nCvSeqsFound] = contour_ptr;	 // copy the pointer
                nCvSeqsFound++;
            }
		}
		contour_ptr = contour_ptr->h_next;
	}
    
    
	// sort the pointers based on size
	if( nCvSeqsFound > 0 ) {
		qsort( cvSeqBlobs, nCvSeqsFound, sizeof(CvSeq*), qsort_carea_compare);
	}


	// now, we have nCvSeqsFound contours, sorted by size in the array 
    // cvSeqBlobs let's get the data out and into our structures that we like
	for( int i = 0; i < MIN(nConsidered, nCvSeqsFound); i++ ) {
		contours.push_back( Contour() );
		float area = cvContourArea( cvSeqBlobs[i], CV_WHOLE_SEQ );
		CvRect rect	= cvBoundingRect( cvSeqBlobs[i], 0 );
		cvMoments( cvSeqBlobs[i], myMoments );
		
		contours[i].area 		= fabs(area);
		contours[i].hole 		= area < 0 ? true : false;
		contours[i].length 		= cvArcLength(cvSeqBlobs[i]);
        contours[i].center.set((myMoments->m10 / myMoments->m00),
                               (myMoments->m01 / myMoments->m00));
        contours[i].box.set(rect.x, _height-rect.y, 0.0, rect.x+rect.width, _height-(rect.y+rect.height), 0.0);
		
		// get the points for the blob:	
        /*
		CvPoint pt;	
		CvSeqReader reader;
		cvStartReadSeq( cvSeqBlobs[i], &reader, 0 );

		for( int j=0; j < cvSeqBlobs[i]->total; j++ ) {
			CV_READ_SEQ_ELEM( pt, reader );
            contours[i].contour.push_back( ofPoint((float)pt.x, (float)pt.y) );
		}
        */

	}


	// Free the storage memory.
	// Warning: do this inside this function otherwise a strange memory leak
	if( contour_storage != NULL ) { cvReleaseMemStorage(&contour_storage); }
	if( storage != NULL ) { cvReleaseMemStorage(&storage); }

}



/*
void ContourFinder::draw( float x, float y ) {
	ofEnableAlphaBlending();
	ofSetColor( 255,0,200,100 );
    glPushMatrix();
    glTranslatef( x, y, 0.0 );
    
	ofNoFill();
	for( int i=0; i<contours.size(); i++ ) {
		ofRect( contours[i].box.x, contours[i].box.y, 
                contours[i].box.width, contours[i].box.height );
	}
	ofDisableAlphaBlending();
	
	ofSetColor(0xffffff);
	for( int i=0; i<contours.size(); i++ ) {
		glBegin(GL_LINE_LOOP);
		for( int j=0; j<contours[i].contour.size(); j++ ) {
			glVertex2f( contours[i].contour[j].x, contours[i].contour[j].y );
		}
		glEnd();
	}
	glPopMatrix();
}
*/

