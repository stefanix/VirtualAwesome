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

#ifndef VA_CIRCLESHAPE
#define VA_CIRCLESHAPE


#include <va/Shape.h>
#include <va/VertexGeometry.h>

namespace va {


class CircleShape : public Shape {

    public:

        CircleShape();
        CircleShape( float radius, int resolution=40 );
        void reshape( float radius, int resolution=40 );        
        void reshape();
        
        void setRadius( float r );
        float getRadius() {return _radius;}        
        void setResolution( int res );
        int getResolution() {return _resolution;}

        void setColor( float r, float g, float b, float a );
        void setColor( const osg::Vec4& color );
        const osg::Vec4& getColor();
               
        void lineMode();
        void fillMode();


    protected:
        float _radius;
        int _resolution;
        osg::ref_ptr<VertexGeometry> _verts;
    
        void init( float radius, int resolution );
};


}
#endif