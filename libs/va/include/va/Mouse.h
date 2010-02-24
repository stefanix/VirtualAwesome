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

#ifndef VA_MOUSE
#define VA_MOUSE

namespace va {

class GuiEvents;
class Scene;


class Mouse {
    public:
        
        enum Button { 
            LEFT_BUTTON    = 1<<0,
            MIDDLE_BUTTON  = 1<<1,
            RIGHT_BUTTON   = 1<<2
        };
        
        enum ButtonDirection { 
            PRESS    = 1<<3,
            RELEASE  = 1<<4
        };        
            
        enum ScrollingMotion {
            SCROLL_NONE,
            SCROLL_LEFT,
            SCROLL_RIGHT,
            SCROLL_UP,
            SCROLL_DOWN,
            SCROLL_2D
        };
        
                                
        Mouse()
          : _id(0),
            _x(0.0f),
            _y(0.0f),
            _button(0),
            _buttonDirection(PRESS),
            _scrollingDeltaX(0.0f),
            _scrollingDeltaY(0.0f),
            _scrollingMotion(SCROLL_NONE),
            _time(0.0)
        {}
        
        float getId() {return _id;}
        float getX() {return _x;}
        void setX( float x ) {_x = x;}
        float getY() {return _y;}
        void setY( float y ) {_y = y;}
        int getButton() {return _button;}
        void setButton( int button ) {_button = button;}
        unsigned int getButtonDirection() {return _buttonDirection;}
        float getScrollingDeltaX() {return _scrollingDeltaX;}
        float getScrollingDeltaY() {return _scrollingDeltaY;}
        ScrollingMotion getScrollingMotion() {return _scrollingMotion;}
        double getTime() {return _time;}

    protected:
    	friend class GuiEvents;
    	friend class Scene;
        int _id;
        float _x;
        float _y;
        int _button;
        int _buttonDirection;
        float _scrollingDeltaX;
        float _scrollingDeltaY;
        ScrollingMotion _scrollingMotion;
        double _time;
};


}
#endif
