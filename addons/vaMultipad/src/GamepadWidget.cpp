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

#include <vaMultipad/GamepadWidget.h>

using namespace vaMultipad;


GamepadWidget::GamepadWidget() {
	init(400);
}
GamepadWidget::GamepadWidget( float w ) {        
	init(w);
}
void GamepadWidget::init( float w ) {
	_multipad = vaMultipad::getMultipad();
    _multipad->addEventHandler(this);
    
    _width = w;
    _height = w/1.5;
    _cornerRadius = 0.05*_height;
    
    _bStick1Event = false;
    _bStick2Event = false;
    _bButton1Event = false;
    _bButton2Event = false;
    _bButton1 = false;
    _bButton2 = false;
        
    enableUpdateCallback();
    
    _background->setColor(0.0, 0.0, 0.0, 0.3);
    // do not draw the border of the background
    _geode->removeDrawable(_border->getOsgGeometry().get());
    
    
    _stickWidth = 0.45*_width;
    _stickWidthPlus = 0.55*_width;
    _buttonHeight = _height-0.5*_width;
    _buttonHeightPlus = _height-0.45*_width;
        
    _slider1 = new va::Slider2DWidget(_stickWidth, _stickWidth);
    _slider1->setLabel("Stick 1");
    _slider1->setValueXMin(-0.2*va::PI);
    _slider1->setValueXMax(0.2*va::PI);
    _slider1->setValueYMin(-0.2*va::PI);
    _slider1->setValueYMax(0.2*va::PI);
    addChild(_slider1);       

    _slider2 = new va::Slider2DWidget(_stickWidth, _stickWidth);
    _slider2->setLabel("Stick 2");
    _slider2->setValueXMin(-0.2*va::PI);
    _slider2->setValueXMax(0.2*va::PI);
    _slider2->setValueYMin(-0.2*va::PI);
    _slider2->setValueYMax(0.2*va::PI);
    addChild(_slider2);
    
    _button1 = new va::ButtonWidget(_stickWidth,_buttonHeight);
    _button1->setLabel("Button1");
    _button1->setCornerRadius(_cornerRadius);    
    addChild(_button1);    

    _button2 = new va::ButtonWidget(_stickWidth,_buttonHeight);
    _button2->setLabel("Button2");
    _button2->setCornerRadius(_cornerRadius);
    addChild(_button2);
        
    
    reshape();
}


void GamepadWidget::reshape() {
    // define geometry
    _background->clearVertices();
    _background->addRoundedRect(0.0f, 0.0f, _width, _height, _cornerRadius);
        
    //make multipad touches scale to gampad size
    _multipad->setScale(_width, _height);
    
    _stickWidth = 0.45*_width;
    _stickWidthPlus = 0.55*_width;
    _buttonHeight = _height-0.5*_width;
    _buttonHeightPlus = _height-0.45*_width;
        
    _slider1->setPivot(0.0,_stickWidth,0);
    _slider1->setPosition(0.0,_height);
    _slider2->setPivot(0.0,_stickWidth,0);
    _slider2->setPosition(_stickWidthPlus,_height);    
    _button2->setPosition(_stickWidthPlus,0.0);
}





void GamepadWidget::addEventHandler( GamepadHandler* handler ){
    _handlers.push_back( handler );
}
std::vector<GamepadHandler*>&  GamepadWidget::getEventHandlers() {
    return _handlers;
}
void GamepadWidget::callHandlers() {
    for( unsigned int i=0; i<_handlers.size(); i++) {
        _handlers[i]->widget( *this );
    }
}


void GamepadWidget::update() {
    _bStick1Event = false;
    _bStick2Event = false;
    _bButton1Event = false;
    _bButton2Event = false;
        
    //handle asynchronous rawTouches, resync!
    _asyncTouchesMutex.lock();
    for( unsigned int i=0; i< _asyncTouches.size(); ++i ){
        va::TouchAsync* touch = _asyncTouches[i];
        va::Touch t = va::Touch();  //dummy to pass
        switch (touch->getType()) {
            case va::TouchAsync::DOWN:
                if (touch->getY() < _buttonHeight) {
                	if (touch->getX() < _stickWidth) {
                        _button1->touchDown(t);
                        _bButton1Event = true;
                        _bButton1 = true;                        
                    } else if (touch->getX() > _stickWidthPlus) {
                        _button2->touchDown(t);
                        _bButton2Event = true;
                        _bButton2 = true;                        
                    }
                }
                callHandlers();              
                break;
            case va::TouchAsync::MOVE:
            	if (touch->getY() > _buttonHeightPlus ) {
            		if (touch->getX() < _stickWidth) {
                        // stick 1
                        float x = va::rangemap(touch->getX(), 0,_stickWidth, -1,1);
                        float y = va::rangemap(touch->getY(), _buttonHeightPlus,_height, -1,1);
                        _slider1->setValueX(x);
                        _slider1->setValueY(y);
                        _bStick1Event = true;
                    } else if (touch->getX() > _stickWidthPlus) {
                        // stick 2
                        float x = va::rangemap(touch->getX(), _stickWidthPlus,_width, -1,1);
                        float y = va::rangemap(touch->getY(), _buttonHeightPlus,_height, -1,1);
                        _slider2->setValueX(x);
                        _slider2->setValueY(y);
                        _bStick2Event = true;
                    }                    
                }
                callHandlers();              
                break;
            case va::TouchAsync::UP:
                if (touch->getY() < _buttonHeight) {
                	if (touch->getX() < _stickWidth) {
                        _button1->touchUp(t);
                        _bButton1Event = true;
                        _bButton1 = false;
                    } else if (touch->getX() > _stickWidthPlus) {
                        _button2->touchUp(t);
                        _bButton2Event = true;
                        _bButton2 = false;
                    }
                }          
                callHandlers();              
                break;
            default:
                break;
        }
        delete touch;
    }
    _asyncTouches.clear();
    _asyncTouchesMutex.unlock(); 
}



// Inject Asynchronous Touch Events
// Use these when called from another thread.
// The events will be resynced with the main thread.
//     
void GamepadWidget::rawTouchEnterAsync( int id, int x, int y, float magnitude ){
	_asyncTouchesMutex.lock();
	_asyncTouches.push_back(new va::TouchAsync(id,x,y,magnitude,va::TouchAsync::ENTER));
    _asyncTouchesMutex.unlock();
}
void GamepadWidget::rawTouchDownAsync( int id, int x, int y, float magnitude ){
	_asyncTouchesMutex.lock();
	_asyncTouches.push_back(new va::TouchAsync(id,x,y,magnitude,va::TouchAsync::DOWN));
    _asyncTouchesMutex.unlock();
}
void GamepadWidget::rawTouchMoveAsync( int id, int x, int y, float magnitude ){
	_asyncTouchesMutex.lock();
	_asyncTouches.push_back(new va::TouchAsync(id,x,y,magnitude,va::TouchAsync::MOVE));
    _asyncTouchesMutex.unlock();
}
void GamepadWidget::rawTouchUpAsync( int id, int x, int y, float magnitude ){
	_asyncTouchesMutex.lock();
	_asyncTouches.push_back(new va::TouchAsync(id,x,y,magnitude,va::TouchAsync::UP));
    _asyncTouchesMutex.unlock();
}
void GamepadWidget::rawTouchLeaveAsync( int id, int x, int y, float magnitude ){
	_asyncTouchesMutex.lock();
	_asyncTouches.push_back(new va::TouchAsync(id,x,y,magnitude,va::TouchAsync::LEAVE));
    _asyncTouchesMutex.unlock();
}
