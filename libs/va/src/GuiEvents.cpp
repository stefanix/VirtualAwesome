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

#include <va/GuiEvents.h>
#include <va/Scene.h>	

using namespace va;


GuiEvents::GuiEvents() {
	_mouseEvent._id = 0;
}

void GuiEvents::addUpdateHandler( UpdateHandler* handler ){
	_updateHandlers.push_back(handler);
}
void GuiEvents::addResizeHandler( ResizeHandler* handler ){
	_resizeHandlers.push_back(handler);
}
void GuiEvents::addKeyHandler( KeyHandler* handler ){
	_keyHandlers.push_back(handler);
}
void GuiEvents::addMouseHandler( MouseHandler* handler ){
	_mouseHandlers.push_back(handler);
}
void GuiEvents::addPenHandler( PenHandler* handler ){
	_penHandlers.push_back(handler);
}
        

bool GuiEvents::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa) {
    switch(ea.getEventType()) {
        // app
        //
        case(osgGA::GUIEventAdapter::RESIZE):
            for(unsigned int i=0; i<_resizeHandlers.size(); ++i) {
            	_resizeHandlers[i]->resize(ea.getWindowWidth(), ea.getWindowHeight());
            }            
            return true;

        /*case(osgGA::GUIEventAdapter::QUIT_APPLICATION):
            for(unsigned int i=0; i<_exitHandlers.size(); ++i) {
            	_exitHandlers[i]->exit();
            }            
            return true;*/

        // key
        //
        case(osgGA::GUIEventAdapter::KEYDOWN):
            _keyEvent._key = ea.getKey();
            _keyEvent._time = _scene->getSimulationTime();
            for(unsigned int i=0; i<_keyHandlers.size(); ++i) {
            	_keyHandlers[i]->keyPress(_keyEvent);
                if(_keyHandlers[i]->getConsumeKeyEvents()) {break;}
            }
            return true;
        case(osgGA::GUIEventAdapter::KEYUP):
            _keyEvent._key = ea.getKey();
            _keyEvent._time = _scene->getSimulationTime();
            for(unsigned int i=0; i<_keyHandlers.size(); ++i) {
            	_keyHandlers[i]->keyRelease(_keyEvent);
                if(_keyHandlers[i]->getConsumeKeyEvents()) {break;}
            }            
            return true;

        // mouse
        //
        case(osgGA::GUIEventAdapter::MOVE):
        	if (_scene->_bUseCursor) {
                _scene->rawTouchMove(_mouseEvent.getId(), ea.getX(), ea.getY(), 1.0f);
            }
            return true;
        case(osgGA::GUIEventAdapter::DRAG):
        	if (_scene->_bUseCursor) {
                _scene->rawTouchMove(_mouseEvent.getId(), ea.getX(), ea.getY(), 1.0f);  
            }
            return true;
        case(osgGA::GUIEventAdapter::PUSH):
                if (_scene->_bUseCursor) {        	
                _scene->rawTouchDown(_mouseEvent.getId(), ea.getX(), ea.getY(), 1.0f);
                
                _mouseEvent._x = ea.getX();
                _mouseEvent._y = ea.getY();
                _mouseEvent._button = ea.getButton();
                //_mouseEvent._buttonMask = ea.getButtonMask();
                _mouseEvent._buttonDirection = Mouse::PRESS;
                _mouseEvent._time = _scene->getSimulationTime();
                for(unsigned int i=0; i<_mouseHandlers.size(); ++i) {
                    _mouseHandlers[i]->mouseButton(_mouseEvent);
                }                
			}
            return true;
        case(osgGA::GUIEventAdapter::RELEASE):
        	if (_scene->_bUseCursor) {        	
                _scene->rawTouchUp(_mouseEvent.getId(), ea.getX(), ea.getY(), 1.0f);
                
                _mouseEvent._x = ea.getX();
                _mouseEvent._y = ea.getY();            
                _mouseEvent._button = ea.getButton();
                //_mouseEvent._buttonMask = ea.getButtonMask();
                _mouseEvent._buttonDirection = Mouse::RELEASE;
                _mouseEvent._time = _scene->getSimulationTime();
                for(unsigned int i=0; i<_mouseHandlers.size(); ++i) {
                    _mouseHandlers[i]->mouseButton(_mouseEvent);
                }               
			}
            return true;
        /*case(osgGA::GUIEventAdapter::DOUBLECLICK):
            _mouseEvent._position.x() = ea.getX();
            _mouseEvent._position.y() = ea.getY();
            _mouseEvent._button = ea.getButton();
            _mouseEvent._buttonMask = ea.getButtonMask();
            _mouseEvent._time = _scene->getSimulationTime();
            for(unsigned int i=0; i<_touchHandlers.size(); ++i) {
                _touchHandlers[i]->mouseDoubleclick(_mouseEvent);
            }            
            return true;*/
        case(osgGA::GUIEventAdapter::SCROLL):
            _mouseEvent._x = ea.getX();
            _mouseEvent._y = ea.getY();            
           	_mouseEvent._button = ea.getButton();
            //_mouseEvent._buttonMask = ea.getButtonMask();
            _mouseEvent._buttonDirection = Mouse::RELEASE;
            _mouseEvent._scrollingDeltaX = ea.getScrollingDeltaX();
            _mouseEvent._scrollingDeltaY = ea.getScrollingDeltaY();
            _mouseEvent._time = _scene->getSimulationTime();
            for(unsigned int i=0; i<_mouseHandlers.size(); ++i) {
            	_mouseHandlers[i]->mouseScroll(_mouseEvent);
            }         
            return true;

        // pen
        //
        case(osgGA::GUIEventAdapter::PEN_PRESSURE):
            _penEvent._x = ea.getX();
            _penEvent._y = ea.getY();
            _penEvent._pressure = ea.getPenPressure();
            _penEvent._time = _scene->getSimulationTime();
            for(unsigned int i=0; i<_penHandlers.size(); ++i) {
                _penHandlers[i]->penPressure(_penEvent);
            }            
            return true;
        case(osgGA::GUIEventAdapter::PEN_ORIENTATION):
            _penEvent._x = ea.getX();
            _penEvent._y = ea.getY();
            _penEvent._tiltX = ea.getPenTiltX();
            _penEvent._tiltY = ea.getPenTiltY();
            _penEvent._rotation = ea.getPenRotation();
            _penEvent._time = _scene->getSimulationTime();
            for(unsigned int i=0; i<_penHandlers.size(); ++i) {
                _penHandlers[i]->penOrientation(_penEvent);
            }            
            return true;
        case(osgGA::GUIEventAdapter::PEN_PROXIMITY_ENTER):
            _penEvent._x = ea.getX();
            _penEvent._y = ea.getY();
            _penEvent._time = _scene->getSimulationTime();
            for(unsigned int i=0; i<_penHandlers.size(); ++i) {
                _penHandlers[i]->penEnter(_penEvent);
            }            
            return true;
        case(osgGA::GUIEventAdapter::PEN_PROXIMITY_LEAVE):
            _penEvent._x = ea.getX();
            _penEvent._y = ea.getY();
            _penEvent._time = _scene->getSimulationTime();
            for(unsigned int i=0; i<_penHandlers.size(); ++i) {
                _penHandlers[i]->penLeave(_penEvent);
            }            
            return true;


        default:
            return false;
    }
}

