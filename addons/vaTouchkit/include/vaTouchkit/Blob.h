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

#ifndef VATOUCHKIT_BLOB
#define VATOUCHKIT_BLOB


#include <vector>
#include <osg/Vec2>
#include <osgText/Text>
#include <va/Constants.h>
#include <va/Shape.h>


namespace vaTouchkit {


class Blob {
    public:

		int id;
        float radius;
        osg::Vec2f center;


        Blob() {
            id = -1;
            radius = 0.0f;
            _gotMatched = false;
            _ghostCount = 0;
        }

        Blob( int x, int y, float r ) {
            id = -1;
            radius = r;
            center.set(x,y);
            _gotMatched = false;
            _ghostCount = 0;
        }
    
    
    protected:
    	friend class BlobTracker;
        // the following members are used 
        // internally by the BlobTracker
    	//osg::Vec2 _centerT1;
    	//osg::Vec2 _centerT2;
        bool _gotMatched;
        int _ghostCount;        
        
};


class BlobPair {
    public:

		Blob* blobT0;
		Blob* blobT1;
        float distanceCache;
        
        
        BlobPair( Blob* b1, Blob* b2 ) {
            blobT0 = b1;
            blobT1 = b2;
            distanceCache = 0.0f;
        }
        
        float distance() {
			float dx = blobT1->center.x() - blobT0->center.x();
			float dy = blobT1->center.y() - blobT0->center.y();
            distanceCache = sqrtf(dx*dx + dy*dy);
            return distanceCache;
        }

};


// used when sorting BlobPair with std::sort(...)
// causing the sorting by distance, ascending
inline bool operator<(const BlobPair& a, const BlobPair& b) {
	return a.distanceCache < b.distanceCache;
}



}
#endif

