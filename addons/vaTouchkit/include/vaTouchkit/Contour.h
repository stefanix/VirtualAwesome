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

#ifndef VATOUCHKIT_CONTOUR
#define VATOUCHKIT_CONTOUR


#include <vector>
#include <osg/Vec2>
#include <osg/BoundingBox>
#include <va/Constants.h>


namespace vaTouchkit {


class Contour {
    public:

        float area;
        float length;
        osg::BoundingBox box;
        osg::Vec2f center;
        bool hole;

        //osg::Vec2Array pts;  // contour vertices
        //int nPts;


        Contour() {
            area = 0.0f;
            length = 0.0f;
            hole = false;
            //nPts = 0;
        }

		/*
        void draw(float x = 0, float y = 0){
            ofNoFill();
            ofSetColor(0x00FFFF);
            ofBeginShape();
            for (int i = 0; i < nPts; i++){
                   ofVertex(x + pts[i].x, y + pts[i].y);
            }
            ofEndShape(true);
            ofSetColor(0xff0099);
            ofRect(x + boundingRect.x, y + boundingRect.y, boundingRect.width, boundingRect.height);
        }
        */
};



}
#endif

