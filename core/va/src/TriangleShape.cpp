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

#include <va/TriangleShape.h>

using namespace va;



TriangleShape::TriangleShape(){
	init(osg::Vec3(0,0,0), osg::Vec3(0,0,0), osg::Vec3(0,0,0));
}
TriangleShape::TriangleShape( float p1x, float p1y, float p1z, 
                              float p2x, float p2y, float p2z, 
                              float p3x, float p3y, float p3z )
{
	init(osg::Vec3(p1x,p1y,p1z), osg::Vec3(p2x,p2y,p2z), osg::Vec3(p3x,p3y,p3z));
}
TriangleShape::TriangleShape( const osg::Vec3& p1, const osg::Vec3& p2, const osg::Vec3& p3 ){
	init(p1,p2,p3);
}
void TriangleShape::init( const osg::Vec3& p1, const osg::Vec3& p2, const osg::Vec3& p3 ){
	_verts = new VertexGeometry();
    _geode->addDrawable(_verts->getOsgGeometry().get());
	_verts->setMode(GL_TRIANGLES);
    _verts->addVertex(p1);
    _verts->addVertex(p2);
    _verts->addVertex(p3);
}

void TriangleShape::reshape( const osg::Vec3& p1, const osg::Vec3& p2, const osg::Vec3& p3 ){
    _verts->setVertex(0, p1);
    _verts->setVertex(1, p2);
    _verts->setVertex(2, p3);
}
void TriangleShape::reshape( float p1x, float p1y, float p1z, 
                             float p2x, float p2y, float p2z, 
                             float p3x, float p3y, float p3z )
{
    _verts->setVertex(0, osg::Vec3(p1x,p1y,p1z));
    _verts->setVertex(1, osg::Vec3(p2x,p2y,p2z));
    _verts->setVertex(2, osg::Vec3(p3x,p3y,p3z));    
}


void TriangleShape::setColor( float r, float g, float b, float a ) {
    _verts->setColor(osg::Vec4(r,g,b,a));
}
void TriangleShape::setColor( const osg::Vec4& color ) {
    _verts->setColor(color);
}
const osg::Vec4& TriangleShape::getColor() {
	return _verts->getColor();
}

void TriangleShape::lineMode(){
	_verts->setMode(GL_TRIANGLES);
}
void TriangleShape::fillMode(){
	_verts->setMode(GL_LINE_LOOP);
}




                            


            