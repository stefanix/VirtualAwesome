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

#include <va/RectangleShape.h>

using namespace va;


RectangleShape::RectangleShape(){
	init(100,100);
}

RectangleShape::RectangleShape( float w, float h ){
	init(w,h);
}
void RectangleShape::init( float w, float h ){
	_verts = new VertexGeometry();
    _geode->addDrawable(_verts->getOsgGeometry().get());
    _verts->setMode(GL_QUADS);
	reshape(w,h);
}


void RectangleShape::reshape( float w, float h ){
	_width = w;
    _height = h;
    reshape();
}
void RectangleShape::reshape(){
	_verts->clearVertices();
    _verts->addVertex(0.f, 0.f, 0.f);
    _verts->addVertex(_width, 0.f, 0.f);
    _verts->addVertex(_width, _height, 0.f);
    _verts->addVertex(0.f, _height, 0.f);
}


void RectangleShape::setWidth( float w ) {
    _width = w;
    reshape();
}
void RectangleShape::setHeight( float h ) {
    _height = h;
    reshape();
} 


void RectangleShape::setColor( float r, float g, float b, float a ) {
    _verts->setColor(osg::Vec4(r,g,b,a));
}
void RectangleShape::setColor( const osg::Vec4& color ) {
    // This binds one color to all verteces.
    _verts->setColor(color);
}
const osg::Vec4& RectangleShape::getColor() {
	return _verts->getColor();
}


void RectangleShape::lineMode(){
	_verts->setMode(GL_QUADS);
}
void RectangleShape::fillMode(){
	_verts->setMode(GL_LINE_LOOP);
}

        