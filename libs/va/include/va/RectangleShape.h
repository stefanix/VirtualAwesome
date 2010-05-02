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

#ifndef VA_RECTANGLESHAPE
#define VA_RECTANGLESHAPE

#include <va/Shape.h>
#include <va/VertexGeometry.h>

namespace va {


class RectangleShape : public Shape {

    public:

        RectangleShape();
        RectangleShape( float w, float h );   
        void reshape( float w, float h );                
        void reshape();
        
        void setWidth( float w );
        float getWidth() { return _width; }
        void setHeight( float h );        
        float getHeight() { return _height; }
        
        void setColor( float r, float g, float b, float a );
        void setColor( const osg::Vec4& color );
        const osg::Vec4& getColor();
               
        void lineMode();
        void fillMode(); 
    
    
    protected:
        float _width;
        float _height;
        osg::ref_ptr<VertexGeometry> _verts;        
    
        void init( float w, float h );
};


}
#endif