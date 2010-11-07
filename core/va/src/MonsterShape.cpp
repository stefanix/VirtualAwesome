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

#include <va/MonsterShape.h>

using namespace va;


MonsterShape::MonsterShape() {
    _body = new VertexShape();
    _body->setMode(GL_POLYGON);
    _body->addVertex(5, 120, 0);     //left elbow
    _body->addVertex(10, 80, 0);
    _body->addVertex(15, 80, 0);
    _body->addVertex(20, 110, 0);
    _body->addVertex(30, 115, 0);
    _body->addVertex(30, 40, 0);
    _body->addVertex(50, 35, 0);
    _body->addVertex(50, 30, 0);
    _body->addVertex(35, 20, 0);
    _body->addVertex(35, 15, 0);
    _body->addVertex(55, 20, 0);
    _body->addVertex(63, 33, 0);
    _body->addVertex(100, 30, 0);
    _body->addVertex(100, 25, 0);
    _body->addVertex(80, 12, 0);
    _body->addVertex(80, 5, 0);      //right big toe
    _body->addVertex(110, 15, 0);
    _body->addVertex(115, 30, 0);
    _body->addVertex(130, 30, 0);
    _body->addVertex(130, 100, 0);
    _body->addVertex(145, 95, 0);
    _body->addVertex(145, 55, 0);
    _body->addVertex(150, 55, 0);
    _body->addVertex(165, 115, 0);   //right elbow
    _body->addVertex(130, 150, 0);
    _body->addVertex(150, 170, 0);
    _body->addVertex(130, 190, 0);
    _body->addVertex(35, 190, 0);
    _body->addVertex(15, 170, 0);
    _body->addVertex(32, 150, 0);
    _body->tesselate();
    addChild(_body);
    

    _mouth = new VertexShape();
    _mouth->setMode(GL_POLYGON);
    _mouth->addVertex(5, 10, 0);
    _mouth->addVertex(10, 25, 0); //
    _mouth->addVertex(68, 23, 0); //
    _mouth->addVertex(72, 0, 0);
    _mouth->addVertex(75, 33, 0);
    _mouth->addVertex(5, 33, 0);
    _mouth->setPosition(40, 120, 0);
    _mouth->tesselate();
    addChild(_mouth);

    _leye = new VertexShape();
    _leye->setMode(GL_POLYGON);
    _leye->addVertex(40, 180, 0);
    _leye->addVertex(40, 170, 0);
    _leye->addVertex(50, 170, 0); 
    _leye->addVertex(50, 180, 0);
    addChild(_leye);

    _reye = new VertexShape();
    _reye->setMode(GL_POLYGON);
    _reye->addVertex(110, 180, 0);
    _reye->addVertex(110, 170, 0);
    _reye->addVertex(120, 170, 0);
    _reye->addVertex(120, 180, 0);
    addChild(_reye);
    
    setColor(1, 0.19, 0.14, 1);
    
    disableDepthTest();
    disableLighting();    
}


void MonsterShape::setColor( float r, float g, float b, float a ) {
    setColor(osg::Vec4(r,g,b,a));
}
    
void MonsterShape::setColor( const osg::Vec4& color ) {
    _body->setColor(color);
    _mouth->setColor(color/3.0f);
    _leye->setColor(color/3.0f);
    _reye->setColor(color/3.0f);
}

