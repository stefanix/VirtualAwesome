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
* The GestureWidget is a Widget that can recognize basic
* multitouch gestures: Two finger drag, pinch-zoom, two finger rotate
* These gestures are then applied in expected ways to the transform
* of the widget.
*
* Internally the GestureWidget uses two transforms. The usual _xform
* and the optional _xform2. Any Node can have this _xform2 enabled and
* it allows for more complex transformations. In this case this is very
* very handy because it makes sure the gesture transforms do not interfer
* with the manual widget transforms in unexpected ways.
*/


#include <va/GestureWidget.h>

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
    _bDraggingEnabled = false;
    _bTwoTouchMoveEnabled = true;
    _bTwoTouchScaleEnabled = true;
    _bTwoTouchRotateEnabled = true;
    
	enableDualXforms();  // use a second _xform2 for gesture transforms
        
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
    	// pivot
        Touch* touch1 = _activeTouches[0];
        Touch* touch2 = _activeTouches[1];    
        osg::Vec3 touchDownMiddle = (_touchDownPosition[touch1] + _touchDownPosition[touch2]) / 2.0;        
        osg::Vec3 touchDownWorldMiddle = (_touchDownWorldPosition[touch1] + _touchDownWorldPosition[touch2]) / 2.0;        
        _xform2->setPivotPoint(touchDownMiddle);  
        _xform2->setPosition(touchDownWorldMiddle);  // compensate position
        
        touchDownScale = _xform2->getScale()[0];
        touchDownQuat = _xform2->getAttitude();
    } else if (_activeTouches.size() == 1) {
        _xform2->setPivotPoint(_touchDownPosition[_activeTouches[0]]);  
        _xform2->setPosition(_touchDownWorldPosition[_activeTouches[0]]);  // compensate position
    }
}  
void GestureWidget::touchMove( Touch& touch ) {
    if (_activeTouches.size() == 2) {
        Touch* touch1 = _activeTouches[0];
        Touch* touch2 = _activeTouches[1];
        
        // position
        if (_bTwoTouchMoveEnabled) {
            osg::Vec3 middle = (touch1->getPosition() + touch2->getPosition()) / 2.0;        
            osg::Matrix mat;
            _xform2->computeLocalToWorldMatrix(mat, NULL);
            osg::Vec3 middleInParent = middle * mat;  // in ref to _xform node
            _xform2->setPosition(middleInParent);        
		}
	  
        // scale
        if (_bTwoTouchScaleEnabled) {
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
		}
		
        // rotation
        if (_bTwoTouchRotateEnabled) {
            osg::Vec2 touchDownFingersVec = _touchDownScreenPosition[touch1] - _touchDownScreenPosition[touch2];
            osg::Vec2 fingersVec = touch1->getScreenPosition() - touch2->getScreenPosition();
            osg::Quat quat;
            quat.makeRotate(osg::Vec3(touchDownFingersVec, 0.0), osg::Vec3(fingersVec, 0.0));
            _xform2->setAttitude(touchDownQuat * quat); 
		}        
    } else if (_activeTouches.size() == 1) {
    	if (_bDraggingEnabled) {
            osg::Matrix mat;
            _xform2->computeLocalToWorldMatrix(mat, NULL);
            _xform2->setPosition(touch.getPosition() * mat);  
        }
    }
}
void GestureWidget::touchUp( Touch& touch ) {}



