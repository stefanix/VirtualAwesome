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

#ifndef VA_EVENTS
#define VA_EVENTS

namespace va {


class UpdateHandler {
    public:
        virtual ~UpdateHandler() {}   
        virtual void update(){}
};

class ResizeHandler {
    public:
        virtual ~ResizeHandler() {}   
        virtual void resize( int w, int h ){}
};


class KeyHandler;
class FirstKeyHandler {
    public:        
        // Keeping track of the firstKeyHandler
        // Used like this:
        // FirstKeyHandler::get()
        // FirstKeyHandler::set(handler)
        static KeyHandler* get() {
            return getManagerInstance()._firstKeyHandler;
        }
        static void set( KeyHandler* handler ) {
            getManagerInstance()._firstKeyHandler = handler;
        }
        
    private:
        KeyHandler* _firstKeyHandler;
        
        FirstKeyHandler() 
          : _firstKeyHandler(NULL)
        {}
        
        static FirstKeyHandler& getManagerInstance() {
            static FirstKeyHandler instance;
            return instance;
        }
};

class Key;
class KeyHandler {
    public:
        KeyHandler() 
          : _consumeKeyEvents(false)  //by default do not consume events
        {}
        virtual ~KeyHandler() {
            // check if this key handler is currently focused
            if (FirstKeyHandler::get() == this) {
                FirstKeyHandler::set(NULL);
            }
        }
        
        virtual void keyPress( Key& key ){}
        virtual void keyRelease( Key& key ){}
        
        virtual bool getConsumeKeyEvents() {
            return _consumeKeyEvents;
        }
        virtual void setConsumeKeyEvents( bool bConsume ) {
            _consumeKeyEvents = bConsume;
        }        
        
    private:
        bool _consumeKeyEvents;
};


class Touch;
class TouchHandler {
    public:
        virtual ~TouchHandler() {} 
        virtual void touchEnter( Touch& touch ){}
        virtual void touchDown( Touch& touch ){}
        virtual void touchMove( Touch& touch ){}
        virtual void touchUp( Touch& touch ){}
        virtual void touchLeave( Touch& touch ){}
};


class Mouse;
class MouseHandler {
    public:
        virtual ~MouseHandler() {}   
        virtual void mouseButton( Mouse& mouse ){}
        virtual void mouseScroll( Mouse& mouse ){}
};


class RawTouchHandler {
    public:
        virtual ~RawTouchHandler() {}   
        virtual void rawTouchEnter( int id, int x, int y, float magnitude ) {}
        virtual void rawTouchDown( int id, int x, int y, float magnitude ) {}
        virtual void rawTouchMove( int id, int x, int y, float magnitude ) {}
        virtual void rawTouchUp( int id, int x, int y, float magnitude ) {}
        virtual void rawTouchLeave( int id, int x, int y, float magnitude ) {}
           
        virtual void rawTouchEnterAsync( int id, int x, int y, float magnitude ) {}
        virtual void rawTouchDownAsync( int id, int x, int y, float magnitude ) {}
        virtual void rawTouchMoveAsync( int id, int x, int y, float magnitude ) {}
        virtual void rawTouchUpAsync( int id, int x, int y, float magnitude ) {}
        virtual void rawTouchLeaveAsync( int id, int x, int y, float magnitude ) {}        
};


class Pen;
class PenHandler {
    public:
        virtual ~PenHandler() {}   
        virtual void penPressure( Pen& pen ){}
        virtual void penOrientation( Pen& pen ){}
        virtual void penEnter( Pen& pen ){}
        virtual void penLeave( Pen& pen ){}
};


class ButtonWidget;
class ButtonHandler {
    public:
        virtual ~ButtonHandler() {}    
        virtual void widget( ButtonWidget& button ){}
};

class Slider2DWidget;
class Slider2DHandler {
    public:
        virtual ~Slider2DHandler() {}    
        virtual void widget( Slider2DWidget& slider ){}
};

class SliderWidget;
class SliderHandler {
    public:
        virtual ~SliderHandler() {}    
        virtual void widget( SliderWidget& slider ){}
};

class ToggleWidget;
class ToggleHandler {
    public:
        virtual ~ToggleHandler() {}   
        virtual void widget( ToggleWidget& toggle ){}
};


}
#endif

