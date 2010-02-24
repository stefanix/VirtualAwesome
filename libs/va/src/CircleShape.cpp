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

#include <va/CircleShape.h>

using namespace va;


CircleShape::CircleShape(){
	init(10,40);
}
CircleShape::CircleShape( float radius, int resolution ){
	init(radius,resolution);
}
void CircleShape::init( float radius, int resolution ){
	_verts = new VertexGeometry();
    _geode->addDrawable(_verts->getOsgGeometry().get());
	_verts->setMode(GL_TRIANGLE_FAN);
	reshape(radius, resolution);
}


void CircleShape::reshape( float radius, int resolution ) {
    _radius = radius;
    //setPivot(0.5*_radius, 0.5*_radius, 0.0f);  
    _resolution = resolution;
    reshape();
}
void CircleShape::reshape() {
    _verts->clearVertices();
    float angle = 0.0f;
    float angleAdder = 2*osg::PI / (float)_resolution;
    for (int i = 0; i < _resolution; i++){
        _verts->addVertex(cos(angle)*_radius, sin(angle)*_radius, 0.0f);
        angle += angleAdder;
    }
}


void CircleShape::setRadius( float r ) {
    _radius = r;
    //setPivot(0.5*_radius, 0.5*_radius, 0.0f);    
    reshape();
}
void CircleShape::setResolution( int res ) {
    if (res > 1) {
        _resolution = res;
        reshape();
    }
}


void CircleShape::setColor( float r, float g, float b, float a ) {
    _verts->setColor(osg::Vec4(r,g,b,a));
}
void CircleShape::setColor( const osg::Vec4& color ) {
    // This binds one color to all vertices.
    _verts->setColor(color);
}
const osg::Vec4& CircleShape::getColor() {
	return _verts->getColor();
}

void CircleShape::lineMode(){
	_verts->setMode(GL_LINE_LOOP);
}
void CircleShape::fillMode(){
	_verts->setMode(GL_TRIANGLE_FAN);
}

  