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


#include <va/VertexShape.h>

using namespace va;


VertexShape::VertexShape() {
    _verts = new VertexGeometry();
    _geode->addDrawable(_verts->getOsgGeometry().get());
}

void VertexShape::setMode( GLenum mode ) {
    _verts->setMode(mode);
}

void VertexShape::setVisible( bool bShow ){
	_verts->setVisible(bShow);
}

void VertexShape::setLineWidth( float width ) {
    _verts->setLineWidth(width);
}



// Vertices
//

void VertexShape::addVertex( float x, float y, float z ) {
    _verts->addVertex(osg::Vec3(x, y, z));
}
void VertexShape::addVertex( const osg::Vec3& vec) {
    _verts->addVertex(vec);
}
void VertexShape::setVertex( unsigned int index, const osg::Vec3& vec ){
    _verts->setVertex(index, vec);   
}
const osg::Vec3& VertexShape::getVertex( unsigned int index ){
    return _verts->getVertex(index);
}
void VertexShape::clearVertices() {
    _verts->clearVertices();
}



// Vertex Colors
//

void VertexShape::setColor( float r, float g, float b, float a ) {
    _verts->setColor(osg::Vec4(r,g,b,a));
}
void VertexShape::setColor( const osg::Vec4& color ) {
    _verts->setColor(color);
}
const osg::Vec4& VertexShape::getColor() {
	return _verts->getColor();
}

void VertexShape::addVertexColor( float r, float g, float b, float a ) {
    _verts->addVertexColor(osg::Vec4(r,g,b,a));
}
void VertexShape::addVertexColor( const osg::Vec4& colorvec ) {
    _verts->addVertexColor(colorvec);
}
void VertexShape::setVertexColor( unsigned int index, const osg::Vec4& colorvec ){
	_verts->setVertexColor(index, colorvec);  
}
const osg::Vec4& VertexShape::getVertexColor( unsigned int index ){
    return _verts->getVertexColor(index);
}
void VertexShape::clearVertexColors() {
    _verts->clearVertexColors();
}



// Vertex Normals
//

void VertexShape::setNormal( float x, float y, float z ){
	_verts->setNormal(osg::Vec3(x,y,z));
}
void VertexShape::setNormal( const osg::Vec3& normal ){
    _verts->setNormal(normal);
}
const osg::Vec3& VertexShape::getNormal(){
	return _verts->getNormal();
}

void VertexShape::addVertexNormal( float x, float y, float z ){
    _verts->addVertexNormal(osg::Vec3(x,y,z));
}
void VertexShape::addVertexNormal( const osg::Vec3& normal ){
    _verts->addVertexNormal(normal);
}
void VertexShape::setVertexNormal( unsigned int index, const osg::Vec3& normal ){
	_verts->setVertexNormal(index, normal);
}
const osg::Vec3& VertexShape::getVertexNormal( unsigned int index ){
    return _verts->getVertexNormal(index);
}
void VertexShape::clearVertexNormals(){
	_verts->clearVertexNormals();
}


    
void VertexShape::tesselate() {
    _verts->tesselate();
}



// OSG stuff
//

void VertexShape::setOsgGeometry( osg::Geometry* geometry ){
	_verts->setOsgGeometry(geometry);
}
osg::ref_ptr<osg::Geometry> VertexShape::getOsgGeometry(){
	return _verts->getOsgGeometry();
}
        
void VertexShape::setOsgVertexArray(osg::Vec3Array* vertices){
	_verts->setOsgVertexArray(vertices);
}
osg::ref_ptr<osg::Vec3Array> VertexShape::getOsgVertexArray(){
	return _verts->getOsgVertexArray();
}
