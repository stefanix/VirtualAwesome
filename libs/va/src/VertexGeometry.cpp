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


#include <va/VertexGeometry.h>

using namespace va;


VertexGeometry::VertexGeometry() {
        
    _geometry = new osg::Geometry();
                
    _vertices = new osg::Vec3Array;       
    _geometry->setVertexArray(_vertices.get());
    
    _colors = new osg::Vec4Array;
    _colors->push_back(osg::Vec4(0.7f, 0.7f, 0.0f, 1.0f));
    _geometry->setColorArray(_colors.get());
    _geometry->setColorBinding(osg::Geometry::BIND_OVERALL);
    bPerVertexColorBindingActive = false;    
    
    _normals = new osg::Vec3Array;
    _normals->push_back(osg::Vec3(0.0f,0.0f,1.0f));
    _geometry->setNormalArray(_normals.get());
    _geometry->setNormalBinding(osg::Geometry::BIND_OVERALL);
    bPerVertexNormalBindingActive = false;
    
    _mode = GL_POINTS;
    _drawArray = new osg::DrawArrays(_mode, 0, _vertices->size());
    _geometry->addPrimitiveSet(_drawArray.get()); 
    
    _bVisible = true;
    _lineWidth = 1.0f;
}

void VertexGeometry::setMode( GLenum mode ) {
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
    _drawArray->set(mode, _drawArray->getFirst(), _drawArray->getCount());
    _geometry->dirtyDisplayList();
    _mode = mode;
}

void VertexGeometry::setVisible( bool bShow ){
	if (bShow) {
    	_bVisible = true;
        setOsgVertexCount(_vertices->size());
    } else {
    	_bVisible = false;
        setOsgVertexCount(0);
    }
}

void VertexGeometry::setLineWidth( float width ) {
	_lineWidth = width;
    osg::StateSet* stateset = _geometry->getOrCreateStateSet();
    osg::LineWidth* lw = new osg::LineWidth(width);
    stateset->setAttributeAndModes(lw, osg::StateAttribute::ON);
}

void VertexGeometry::dirty(){
	_geometry->dirtyDisplayList();
}



// Vertices
//

void VertexGeometry::addVertex( float x, float y, float z ) {
    addVertex(osg::Vec3(x, y, z));
}
void VertexGeometry::addVertex( const osg::Vec3& vec) {
    _vertices->push_back(vec);
    if (_bVisible) {
        _drawArray->setCount(_vertices->size());
        _geometry->dirtyDisplayList();
	}
}
void VertexGeometry::setVertex( unsigned int index, const osg::Vec3& vec ){
	_vertices->at(index) = vec;
    _geometry->dirtyDisplayList();    
}
const osg::Vec3& VertexGeometry::getVertex( unsigned int index ){
    return _vertices->at(index);
}
void VertexGeometry::clearVertices() {
    _vertices->clear();
}



// Vertex Colors
//

void VertexGeometry::setColor( float r, float g, float b, float a ) {
    setColor(osg::Vec4(r,g,b,a));
}
void VertexGeometry::setColor( const osg::Vec4& color ) {
    // This bind one color to all verteces.
    _colors->clear();
    _colors->push_back(color);
    _geometry->setColorBinding(osg::Geometry::BIND_OVERALL);
    _geometry->dirtyDisplayList();
    bPerVertexColorBindingActive = false;
}
const osg::Vec4& VertexGeometry::getColor() {
	return _colors->at(0);
}

void VertexGeometry::addVertexColor( float r, float g, float b, float a ) {
    addVertexColor(osg::Vec4(r,g,b,a));
}
void VertexGeometry::addVertexColor( const osg::Vec4& colorvec ) {
    // Once you start adding colors you are switiching to per-vertex mode.
    // This also means you need to have exactly one color per vertex.
    if( !bPerVertexColorBindingActive) {
        // The first time this is called clear all colors.
        _colors->clear();
        bPerVertexColorBindingActive = true;
    }
    _colors->push_back(colorvec);
    _geometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
    _geometry->dirtyDisplayList();
}
void VertexGeometry::setVertexColor( unsigned int index, const osg::Vec4& colorvec ){
	_colors->at(index) = colorvec;
    _geometry->dirtyDisplayList();    
}
const osg::Vec4& VertexGeometry::getVertexColor( unsigned int index ){
    return _colors->at(index);
}
void VertexGeometry::clearVertexColors() {
    _colors->clear();
}



// Vertex Normals
//

void VertexGeometry::setNormal( float x, float y, float z ){
	setNormal(osg::Vec3(x,y,z));
}
void VertexGeometry::setNormal( const osg::Vec3& normal ){
    // This binds one color to all vertices.
    _normals->clear();
    _normals->push_back(normal);
    _geometry->setNormalBinding(osg::Geometry::BIND_OVERALL);
    _geometry->dirtyDisplayList();
    bPerVertexNormalBindingActive = false;
}
const osg::Vec3& VertexGeometry::getNormal(){
	return _normals->at(0);
}

void VertexGeometry::addVertexNormal( float x, float y, float z ){
    addVertexNormal(osg::Vec3(x,y,z));
}
void VertexGeometry::addVertexNormal( const osg::Vec3& normal ){
    // Once you start adding normals you are switiching to per-vertex mode.
    // This also means you need to have exactly one normal per vertex.
    if( !bPerVertexNormalBindingActive) {
        // The first time this is called clear all normals.
        _normals->clear();
        bPerVertexNormalBindingActive = true;
    }
    _normals->push_back(normal);
    _geometry->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
    _geometry->dirtyDisplayList(); 
}
void VertexGeometry::setVertexNormal( unsigned int index, const osg::Vec3& normal ){
	_normals->at(index) = normal;
    _geometry->dirtyDisplayList();
}
const osg::Vec3& VertexGeometry::getVertexNormal( unsigned int index ){
    return _normals->at(index);
}
void VertexGeometry::clearVertexNormals(){
	_normals->clear();
}
        

    
void VertexGeometry::tesselate() {
    if( ! _tesselator.valid() ) {
        _tesselator = new osgUtil::Tessellator();
        _tesselator->setWindingType( osgUtil::Tessellator::TESS_WINDING_ODD);
    }
    _tesselator->retessellatePolygons(*(_geometry.get()));
}




void VertexGeometry::addRoundedRect( float x, float y, float w, float h, float r ) {
    addVertex(x+r, y, 0.0f);
    addVertex(x+w-r, y, 0.0f);
    roundedCorner( x+w-r, y, x+w-r, y+r );
    addVertex(x+w, y+r, 0.0f);
    addVertex(x+w, y+h-r, 0.0f);
    roundedCorner( x+w, y+h-r, x+w-r, y+h-r );
    addVertex(x+w-r, y+h, 0.0f);
    addVertex(x+r, y+h, 0.0f);
    roundedCorner( x+r, y+h, x+r, y+h-r );
    addVertex(x, y+h-r, 0.0f);
    addVertex(x, y+r, 0.0f);
    roundedCorner( x, y+r, x+r, y+r );
    addVertex(x+r, y, 0.0f);
}
void VertexGeometry::roundedCorner( float x, float y, float pivotX, float pivotY ) {
    float a = osg::PI*0.125;  //0.5*PI is 90deg
    addVertex( ((x-pivotX)*cos(a) - (y-pivotY)*sin(a)) + pivotX, 
               ((x-pivotX)*sin(a) + (y-pivotY)*cos(a)) + pivotY,
                 0.0f );
    a = osg::PI*0.1875;
    addVertex( ((x-pivotX)*cos(a) - (y-pivotY)*sin(a)) + pivotX, 
               ((x-pivotX)*sin(a) + (y-pivotY)*cos(a)) + pivotY,
                 0.0f );
    a = osg::PI*0.25;
    addVertex( ((x-pivotX)*cos(a) - (y-pivotY)*sin(a)) + pivotX, 
               ((x-pivotX)*sin(a) + (y-pivotY)*cos(a)) + pivotY,
                 0.0f );
    a = osg::PI*0.3125;
    addVertex( ((x-pivotX)*cos(a) - (y-pivotY)*sin(a)) + pivotX, 
               ((x-pivotX)*sin(a) + (y-pivotY)*cos(a)) + pivotY,
                 0.0f );
    a = osg::PI*0.375;
    addVertex( ((x-pivotX)*cos(a) - (y-pivotY)*sin(a)) + pivotX, 
               ((x-pivotX)*sin(a) + (y-pivotY)*cos(a)) + pivotY,
                 0.0f );
    a = osg::PI*0.4375;
    addVertex( ((x-pivotX)*cos(a) - (y-pivotY)*sin(a)) + pivotX, 
               ((x-pivotX)*sin(a) + (y-pivotY)*cos(a)) + pivotY,
                 0.0f );
}



// OSG stuff
//

void VertexGeometry::setOsgGeometry( osg::Geometry* geometry ){	
	//_geometry->unref();
	//_vertices->unref();
	//_drawArray->unref();
	//_colors->unref();
	//_normals->unref();
	_geometry = geometry;
}
osg::ref_ptr<osg::Geometry> VertexGeometry::getOsgGeometry(){
	return _geometry;
}
        
void VertexGeometry::setOsgVertexArray( osg::Vec3Array* vertices) {
    _geometry->setVertexArray(vertices);
    //_vertices->unref();  // not necessary, caused a nasty heap corruption
    _vertices = vertices;
    _drawArray->setCount(_vertices->size());
}
osg::ref_ptr<osg::Vec3Array> VertexGeometry::getOsgVertexArray(){
	return _vertices;
}

void VertexGeometry::setOsgVertexCount( int num ){
	_drawArray->setCount(num);
    _geometry->dirtyDisplayList();
}
int VertexGeometry::getOsgVertexCount(){
	return (int)_vertices->size();
}
