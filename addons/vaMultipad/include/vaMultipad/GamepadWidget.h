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

#ifndef VA_GAMEPADWIDGET
#define VA_GAMEPADWIDGET

#include <vector>
#include <va/Touch.h>
#include <va/Widget.h>
#include <va/Slider2DWidget.h>
#include <va/ButtonWidget.h>
#include <vaMultipad/Multipad.h>

namespace vaMultipad {


class GamepadWidget;
class GamepadHandler {
    public:
        virtual ~GamepadHandler() {}   
        virtual void widget( GamepadWidget& gamepad ){}
};


class GamepadWidget: public va::Widget, public va::RawTouchHandler {

    public:

        GamepadWidget();
        GamepadWidget( float w );  // height will be w/1.5
        void reshape();
        using Widget::reshape;
        
        bool isStick1Event() {return _bStick1Event;}
        bool isStick2Event() {return _bStick2Event;}
        bool isButton1Event() {return _bButton1Event;}
        bool isButton2Event() {return _bButton2Event;}
                
        osg::Vec2 getStick1() {return osg::Vec2(_slider1->getValueX(),_slider1->getValueY());}
        osg::Vec2 getStick2() {return osg::Vec2(_slider2->getValueX(),_slider2->getValueY());}
        bool getButton1() {return _bButton1;}
        bool getButton2() {return _bButton2;}
                
        void update();
        
        void rawTouchEnterAsync( int id, int x, int y, float magnitude );
        void rawTouchDownAsync( int id, int x, int y, float magnitude );
        void rawTouchMoveAsync( int id, int x, int y, float magnitude );
        void rawTouchUpAsync( int id, int x, int y, float magnitude );
        void rawTouchLeaveAsync( int id, int x, int y, float magnitude );
        
        void addEventHandler( GamepadHandler* handler );
        std::vector<GamepadHandler*>&  getEventHandlers();
    
    
    protected:
    
    	Multipad* _multipad;
        std::vector<va::TouchAsync*>  _asyncTouches;   // these are touches coming in through the async injection calls
        OpenThreads::Mutex _asyncTouchesMutex;
        std::vector<GamepadHandler*> _handlers;        

        osg::ref_ptr<va::Slider2DWidget> _slider1;
        osg::ref_ptr<va::Slider2DWidget> _slider2;
        osg::ref_ptr<va::ButtonWidget> _button1;
        osg::ref_ptr<va::ButtonWidget> _button2;
        
        bool _bStick1Event;
        bool _bStick2Event;
        bool _bButton1Event;
        bool _bButton2Event;
        bool _bButton1;
        bool _bButton2;
        
        float _stickWidth;
        float _stickWidthPlus;    // plus gap
        float _buttonHeight;
        float _buttonHeightPlus;  // plus gap
        
        void init( float w );
        void callHandlers();
        
};


}
#endif