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

#ifndef VA_TRIANGLESHAPE
#define VA_TRIANGLESHAPE

#include <va/Shape.h>
#include <va/VertexGeometry.h>

namespace va {


class TriangleShape : public Shape {

    public:

        TriangleShape();                              
        TriangleShape( float p1x, float p1y, float p1z, 
                       float p2x, float p2y, float p2z, 
                       float p3x, float p3y, float p3z );                                      
        TriangleShape( const osg::Vec3& p1, const osg::Vec3& p2, const osg::Vec3& p3 );

        void reshape( const osg::Vec3& p1, const osg::Vec3& p2, const osg::Vec3& p3 );
        void reshape( float p1x, float p1y, float p1z, 
                      float p2x, float p2y, float p2z, 
                      float p3x, float p3y, float p3z );
                              
        void setColor( float r, float g, float b, float a );
        void setColor( const osg::Vec4& color );
        const osg::Vec4& getColor();
               
        void lineMode();
        void fillMode();   
                                                                              

    protected:
        osg::ref_ptr<VertexGeometry> _verts;
        
        void init( const osg::Vec3& p1, const osg::Vec3& p2, const osg::Vec3& p3 );
};


}
#endif