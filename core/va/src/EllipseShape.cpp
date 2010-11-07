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

#include <va/EllipseShape.h>

using namespace va;


EllipseShape::EllipseShape(){
	init(150,100,40);
}
EllipseShape::EllipseShape( float w, float h, int resolution ){
	init(w,h,resolution);
}
void EllipseShape::init( float w, float h, int resolution ){
	_verts = new VertexGeometry();
    _geode->addDrawable(_verts->getOsgGeometry().get());
	_verts->setMode(GL_TRIANGLE_FAN);
	reshape(w,h,resolution);
}


void EllipseShape::reshape( float w, float h, int resolution ) {
	_width = w;
    _height = h;
    setPivot(0.5*_width, 0.5*_height, 0.0f);    
    _resolution = resolution;
    reshape();
}
void EllipseShape::reshape() {
    _verts->clearVertices();
    float angle = 0.0f;
    float angleAdder = 2*osg::PI / (float)_resolution;
    for (int i = 0; i < _resolution; i++){
        _verts->addVertex(cos(angle)*_width*0.5, sin(angle)*_height*0.5, 0.0f);
        angle += angleAdder;
    }
}


void EllipseShape::setWidth( float w ) {
    _width = w;
    setPivot(0.5*_width, 0.5*_height, 0.0f);    
    reshape();
}
void EllipseShape::setHeight( float h ) {
    _height = h;
    setPivot(0.5*_width, 0.5*_height, 0.0f);    
    reshape();
}
void EllipseShape::setResolution( int res ) {
    if (res > 1) {
        _resolution = res;
        reshape();
    }
}


void EllipseShape::setColor( float r, float g, float b, float a ) {
    _verts->setColor(osg::Vec4(r,g,b,a));
}
void EllipseShape::setColor( const osg::Vec4& color ) {
    // This binds one color to all vertices.
    _verts->setColor(color);
}
const osg::Vec4& EllipseShape::getColor() {
	return _verts->getColor();
}

void EllipseShape::lineMode(){
	_verts->setMode(GL_TRIANGLE_FAN);
}
void EllipseShape::fillMode(){
	_verts->setMode(GL_LINE_LOOP);
}



  