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

#include <va/Widget.h>

using namespace va;


Widget::Widget() {
    
    // background
    _background = new VertexGeometry();
    _background->setMode(GL_TRIANGLE_FAN);
    _background->setColor(0.0f, 0.0f, 0.0f, 1.0f);
    _geode->addDrawable(_background->getOsgGeometry().get());
    
    // border
    _border = new VertexGeometry();
    _border->setMode(GL_LINE_LOOP);
    _border->setOsgVertexArray(_background->getOsgVertexArray().get()); //reuse vertices
    _border->setColor(0.5f, 0.5f, 0.5f, 0.8f);
    _geode->addDrawable(_border->getOsgGeometry().get());    
    
    // enable the call to the update(...) method  during updateTraversal
    enableUpdateCallback();
    
    //state
    disableLighting();
    disableDepthTest();
    enableBlending();
    _bTouchEventsEnabled = true;
    _bTouchEventsEnabledSticky = true;  // used in WidgetTouchEventVisitor
    
    //state - line
    osg::StateSet* stateset = _geode->getOrCreateStateSet();
    stateset->setMode(GL_LINE_SMOOTH, osg::StateAttribute::ON);
    osg::LineWidth* lw = new osg::LineWidth(2.5);
    stateset->setAttributeAndModes(lw, osg::StateAttribute::ON);    
    
}

void Widget::reshape( float w, float h ) {
    _width = w;    
    _height = h;
    reshape();    
} 



void Widget::setWidth( float w ) {
    _width = w;
    reshape();
}
void Widget::setHeight( float h ) {
    _height = h;
    reshape();
}



void Widget::setName( const std::string& name) {
    _xform->setName(name);
    _geode->setName(name);
}
const std::string& Widget::getName() {
    return _geode->getName();
}

void Widget::setZIndex(long zIndex) {
    _zIndex = zIndex;
    _xform->getOrCreateStateSet()->setRenderBinDetails(_zIndex, "RenderBin");
}
long Widget::getZIndex() {
    return _zIndex;
}

     

void Widget::setBackgroundColor( float r, float g, float b, float a ) {
    _background->setColor(osg::Vec4(r,g,b,a));
}
void Widget::setBackgroundColor( const osg::Vec4& color ) {
    _background->setColor(color);
}
const osg::Vec4& Widget::getBackgroundColor() {
	return _background->getColor();
}

void Widget::setBorderColor( float r, float g, float b, float a ) {
    _border->setColor(osg::Vec4(r,g,b,a));
}
void Widget::setBorderColor( const osg::Vec4& color ) {
    _border->setColor(color);
}
const osg::Vec4& Widget::getBorderColor() {
	return _border->getColor();
}


void Widget::setXY( const osg::Vec3& pnt ) {  // convinience method for setting pos in the x,y plane
    const osg::Vec3d& pos = getPosition(); 
    setPosition(pnt[0], pnt[1], pos[2]);    
}
void Widget::addXY( const osg::Vec3& pnt ) {  // convinience method for adding to pos in the x,y plane
    const osg::Vec3d& pos = getPosition(); 
    setPosition(pos[0]+pnt[0], pos[1]+pnt[1], pos[2]);    
}    
void Widget::setPosition( float x, float y, float z) {
    _xform->setPosition(osg::Vec3(x, y, z));
}


bool Widget::isDragging( Touch& touch ) {
    if( _touchDownLocalPosition.find(&touch) != _touchDownLocalPosition.end() ) {    
        return true;
    } else {
        return false;
    }
}
const osg::Vec3& Widget::getDragDelta( Touch& touch ) {
    _dragDelta = touch.getPosition() - _touchDownLocalPosition[&touch];   
    return _dragDelta;
}
const osg::Vec3& Widget::getWorldDragDelta( Touch& touch ) {
    osg::Matrix xformMat;
    _xform->computeLocalToWorldMatrix(xformMat, NULL);
    _worldDragDelta = osg::Matrixd::transform3x3(getDragDelta( touch ), xformMat);
    return _worldDragDelta;
}



void Widget::touchDown( Touch& touch ) {
    osg::notify(osg::INFO) << "touchDown on: " << getName() << std::endl;
}  
void Widget::touchMove( Touch& touch ) {
    osg::notify(osg::INFO) << "touchMove on: " << getName() << std::endl;
}
void Widget::touchUp( Touch& touch ) {
    osg::notify(osg::INFO) << "touchUp on: " << getName() << std::endl;
}

void Widget::enableTouchEvents() {
	_bTouchEventsEnabled = true;
	_bTouchEventsEnabledSticky = true;
}
void Widget::disableTouchEvents() {
	_bTouchEventsEnabled = false;
    _bTouchEventsEnabledSticky = false;
}



void Widget::touchDownInternal( Touch& touch ) {
    _touchDownLocalPosition[&touch] = touch.getPosition();
    
    // Walk up the tree and focus parents.
    // This means two things: (1) bring each parent to the 
    // front that returns true on wantsToFrontOnTouch()
    // This typically applies to PanelWidgets.
    // (2) assign keyboard focus to first parent that 
    // returns ture on wantsKeyFocusOnTouch()
    // This typically applies to text input Widgets.
    _widgetFocusVisitor.reset();
    _xform->accept(_widgetFocusVisitor);
    
    touchDown(touch);
}  
void Widget::touchMoveInternal( Touch& touch ) {
    touchMove(touch);
}
void Widget::touchUpInternal( Touch& touch ) {
    touchUp(touch);
    _touchDownLocalPosition.erase(&touch);
}



float Widget::rangemap(float r1val, float r1min, float r1max, float r2min, float r2max) {
    /**
    *                     r1val
    *    |- - - - -|--------x----|
    *    0       r1min       \  r1max
    *                         \
    *    |- - - - - -|---------x-------|
    *    0         r2min      return  r2max
    */
    return (r1val - r1min) * ((r2max - r2min)/(r1max - r1min)) + r2min;
}
