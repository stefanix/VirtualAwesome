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


#include "GestureWidget.h"

using namespace va;


GestureWidget::GestureWidget(){
	init(200,80);
}
GestureWidget::GestureWidget( float w, float h ){
	init(w,h);
}  
void GestureWidget::init( float w, float h ) {  
    setPosition(0.0f, 0.0f, 0.0f);
    _width = w;
    _height = h;
    
	enableDualXforms();  // use a second _xform2 for gesture transforms
    
    _touchShapeMiddle = new va::TouchShape();
    _touchShapeMiddle->setText("middle");
    addChild(_touchShapeMiddle);

    _touchShapeWorldMiddle = new va::TouchShape();
    _touchShapeWorldMiddle->setText("worldMiddle");
    //addChild(_touchShapeWorldMiddle);
    _xform->addChild(_touchShapeWorldMiddle->getOsgXForm().get());
    
    reshape();
}


void GestureWidget::reshape() {
    // define geometry
    _background->clearVertices();
    _background->setColor(0.0f, 0.0f, 0.0f, 0.4f);
    _background->addRoundedRect(0.0f, 0.0f, _width, _height, 8.f);    
}



// Touch Events
//
void GestureWidget::touchDown( Touch& touch ) {
	if (_activeTouches.size() == 2) {
        Touch* touch1 = _activeTouches[0];
        Touch* touch2 = _activeTouches[1];    
        osg::Vec3 touchDownMiddle = (_touchDownPosition[touch1] + _touchDownPosition[touch2]) / 2.0;        
        osg::Vec3 touchDownWorldMiddle = (_touchDownWorldPosition[touch1] + _touchDownWorldPosition[touch2]) / 2.0;        
        _xform2->setPivotPoint(touchDownMiddle);  
        _xform2->setPosition(touchDownWorldMiddle);
        
        touchDownScale = _xform2->getScale()[0];
        touchDownQuat = _xform2->getAttitude();
    }
}  
void GestureWidget::touchMove( Touch& touch ) {
    //if( isDragging(touch) ) {
    //    addPosition(getWorldDragDelta(touch));
    //}
    if (_activeTouches.size() == 2) {
        Touch* touch1 = _activeTouches[0];
        Touch* touch2 = _activeTouches[1];
        
        osg::Vec3 middle = (touch1->getPosition() + touch2->getPosition()) / 2.0;
        _touchShapeMiddle->setPosition(middle);
        
        
        osg::Matrix xform3Mat;
        _xform2->computeLocalToWorldMatrix(xform3Mat, NULL);
        osg::Vec3 worldMiddle = osg::Matrixd::transform3x3(middle, xform3Mat);
        worldMiddle = middle * xform3Mat;
        _touchShapeWorldMiddle->setPosition(worldMiddle);
        
        _xform2->setPosition(worldMiddle);        
        
        //std::cout << touch1->getId() << " : " << touch2->getId() << std::endl;
        
        // pivot and position
        /*
        osg::Vec3 touchDownWorldMiddle = (_touchDownWorldPosition[touch1] + _touchDownWorldPosition[touch2]) / 2.0;
        osg::Vec3 worldMiddle = (touch1->getWorldPosition() + touch2->getWorldPosition()) / 2.0;
        osg::Vec3 middleDelta = worldMiddle - touchDownWorldMiddle;
        osg::Vec3 touchDownMiddle = (_touchDownPosition[touch1] + _touchDownPosition[touch2]) / 2.0;
        
        osg::Vec3 pivotDelta = touchDownMiddle - _xform2->getPivotPoint();
        _xform2->setPivotPoint(touchDownMiddle);
        //_xform2->setPosition(touchDownMiddle +(worldMiddle-touchDownWorldMiddle));  // compensate for new pivot
        _xform2->setPosition(_xform2->getPosition() + pivotDelta + (worldMiddle-touchDownWorldMiddle));  // compensate for new pivot
        //_xform2->setPosition(_xform2->getPosition() + touchDownMiddleLocal - _xform2->getPivotPoint());  // compensate for new pivot
		//addPosition(worldMiddle-touchDownWorldMiddle);
        */
        
        //osg::Vec3 prevWorldMiddle = (touch1->getPreviousWorldPosition() + touch2->getPreviousWorldPosition()) / 2.0;
        //osg::Vec3 worldMiddle = (touch1->getWorldPosition() + touch2->getWorldPosition()) / 2.0;
        //_xform2->setPosition(_xform2->getPosition() + (worldMiddle-prevWorldMiddle));

        //osg::Vec3 worldMiddle = (touch1->getWorldPosition() + touch2->getWorldPosition()) / 2.0;
        //_xform2->setPivotPoint(middle); 
        //_touchShapeMiddle->setPosition(middle); 
        
        
        

        /*
        osg::Vec3 prevMiddle = (touch1->getPreviousPosition() + touch2->getPreviousPosition()) / 2.0;
        osg::Vec3 middle = (touch1->getPosition() + touch2->getPosition()) / 2.0;
        osg::Vec3 middleDelta = middle - prevMiddle;
        osg::Vec3 pivotDelta = middleDelta - _xform2->getPivotPoint();
        _xform2->setPivotPoint(_xform2->getPivotPoint() + middleDelta);
        _xform2->setPosition(_xform2->getPosition() + pivotDelta);
        */
        
        // scale
        float touchDownDistance = (_touchDownScreenPosition[touch1] 
                            - _touchDownScreenPosition[touch2]).length();
        float distance = (touch1->getScreenPosition() - touch2->getScreenPosition()).length();
        float distanceDelta;
        if (touchDownDistance > 0.0) {
            distanceDelta = distance / touchDownDistance;
        } else {
            distanceDelta = 1.0;
        }
        float scale = touchDownScale * distanceDelta;
        _xform2->setScale(osg::Vec3(scale,scale,scale));        

		
        // rotation
        osg::Vec2 touchDownFingersVec = _touchDownScreenPosition[touch1] - _touchDownScreenPosition[touch2];
        osg::Vec2 fingersVec = touch1->getScreenPosition() - touch2->getScreenPosition();
        osg::Quat quat;
        quat.makeRotate(osg::Vec3(touchDownFingersVec, 0.0), osg::Vec3(fingersVec, 0.0));
        _xform2->setAttitude(touchDownQuat * quat); 
        
    }
}
void GestureWidget::touchUp( Touch& touch ) {}



