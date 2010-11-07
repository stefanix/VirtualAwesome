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

#ifndef VA_ELLIPSESHAPE
#define VA_ELLIPSESHAPE

#include <va/Shape.h>
#include <va/VertexGeometry.h>

namespace va {


class EllipseShape : public Shape {

    public:

        EllipseShape();
        EllipseShape( float w, float h, int resolution=40 );
        void reshape( float w, float h, int resolution=40 );        
        void reshape();        
        
        void setWidth( float w );
        float getWidth() {return _width;}
        void setHeight( float h );
        float getHeight() {return _height;}
        void setResolution( int res );
        int getResolution() {return _resolution;}
                
        void setColor( float r, float g, float b, float a );
        void setColor( const osg::Vec4& color );
        const osg::Vec4& getColor();
               
        void lineMode();
        void fillMode();
        
    
    protected:
        float _width;
        float _height;
        int _resolution;
        osg::ref_ptr<VertexGeometry> _verts;        
    
        void init( float w, float h, int resolution );
};


}
#endif