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

#ifndef VA_VERTEXSHAPE
#define VA_VERTEXSHAPE

#include <va/Shape.h>
#include <va/VertexGeometry.h>

namespace va {


class VertexShape : public Shape {
    public:

        VertexShape();
                    
        // mode is one of the following
        // osg::PrimitiveSet::POINTS  or  GL_POINTS
        // osg::PrimitiveSet::LINES  or  GL_LINES
        // osg::PrimitiveSet::LINE_STRIP  or  GL_LINE_STRIP
        // osg::PrimitiveSet::LINE_LOOP  or  GL_LINE_LOOP
        // osg::PrimitiveSet::TRIANGLES  or  GL_TRIANGLES
        // osg::PrimitiveSet::TRIANGLE_STRIP  or  GL_TRIANGLE_STRIP
        // osg::PrimitiveSet::TRIANGLE_FAN  or  GL_TRIANGLE_FAN
        // osg::PrimitiveSet::QUADS  or  GL_QUADS, 
        // osg::PrimitiveSet::QUAD_STRIP  or  GL_QUAD_STRIP
        // osg::PrimitiveSet::POLYGON  or  GL_POLYGON
        void setMode( GLenum mode );
        GLenum getMode() {return _verts->getMode();}
        void setVisible( bool bShow );
        bool getVisible() {return _verts->getVisible();}  
        void setLineWidth( float width );
        float getLineWidth() {return _verts->getLineWidth();}            
        
        
        // Vertices
        //
        void addVertex( float x, float y, float z );
        void addVertex( const osg::Vec3& vec );
        void setVertex( unsigned int index, const osg::Vec3& vec );
        const osg::Vec3& getVertex( unsigned int index );
        void clearVertices();


        // Vertex Colors
        //
        // one color for all vertices
        void setColor( float r, float g, float b, float a );
        void setColor( const osg::Vec4& color );
        const osg::Vec4& getColor();
        // per vertex color                  
        void addVertexColor( float r, float g, float b, float a );
        void addVertexColor( const osg::Vec4& colorvec );
        void setVertexColor( unsigned int index, const osg::Vec4& colorvec );
        const osg::Vec4& getVertexColor( unsigned int index );
        void clearVertexColors();


        // Vertex Normals
        //
        // one normal for all vertices
        void setNormal( float x, float y, float z );
        void setNormal( const osg::Vec3& color );
        const osg::Vec3& getNormal();
        // per vertex normals                  
        void addVertexNormal( float x, float y, float z );
        void addVertexNormal( const osg::Vec3& normal );
        void setVertexNormal( unsigned int index, const osg::Vec3& normal );
        const osg::Vec3& getVertexNormal( unsigned int index );
        void clearVertexNormals();
        
        
        void tesselate();
        
        void addRoundedRect( float x, float y, float w, float h, float r );
        
        // OSG stuff
        void setOsgGeometry( osg::Geometry* geometry );
        osg::ref_ptr<osg::Geometry> getOsgGeometry();
        void setOsgVertexArray(osg::Vec3Array* vertices);
        osg::ref_ptr<osg::Vec3Array> getOsgVertexArray();
        
                
    protected:
      
        osg::ref_ptr<VertexGeometry> _verts;
    
};


}
#endif
