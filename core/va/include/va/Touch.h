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

#ifndef VA_TOUCH
#define VA_TOUCH

#include <osg/Vec2>
#include <osg/Vec3>
#include <va/TouchShape.h>

namespace va {

class Widget;
class Scene;


class Touch {
    public:
        
        Touch()
          : _id(-1),
            _magnitude(0.0f),
            _widget(NULL),
            _scene(NULL),
            //_tapCount(0),
            _time(0),
            //_phase(0),
            _touchShape(NULL)
        {}
        
        Touch( int id, float x, float y, float magnitude )
          : _id(id),
            _position(x,y,0.0f),
            _prevPosition(x,y,0.0f),
            _worldPosition(x,y,0.0f),
            _prevWorldPosition(x,y,0.0f),
            _screenPosition(x,y),
            _prevScreenPosition(x,y),
            _magnitude(magnitude),
            _widget(NULL),
            _scene(NULL),
            //_tapCount(0),
            _time(0),
            //_phase(0),
            _touchShape(NULL)          
        {}
        
        int getId() {return _id;}
        
        const osg::Vec3& getPosition() {return _position;}
        float getX() {return _position.x();}
        float getY() {return _position.y();}        
        const osg::Vec3& getPreviousPosition() {return _prevPosition;}

        const osg::Vec3& getWorldPosition() {return _worldPosition;}
        float getWorldX() {return _worldPosition.x();}
        float getWorldY() {return _worldPosition.y();}        
        const osg::Vec3& getPreviousWorldPosition() {return _prevWorldPosition;}
                        
        const osg::Vec2& getScreenPosition() {return _screenPosition;}
        float getScreenX() {return _screenPosition.x();}
        float getScreenY() {return _screenPosition.y();}
        const osg::Vec2& getPreviousScreenPosition() {return _prevScreenPosition;}
              
        float getMagnitude() {return _magnitude;}        

        Widget* getWidget() {return _widget;} 
        Scene* getScene() {return _scene;}
        
        //int getTapCount() {return _tapCount;}
        double getTime() {return _time;}
        //int getPhase() {return _phase;}
        
        TouchShape* getTouchShape() {return _touchShape;}
                                    
        //virtual osg::Vec3 getLocationInView() { return globalLocation; }
        //virtual osg::Vec3 getPreviousLocationInView() {}

                
   
    //protected:  //FIXME, GamepadWidget
        friend class Scene;
        int _id;
        osg::Vec3 _position;
        osg::Vec3 _prevPosition;        
        osg::Vec3 _worldPosition;      //position in parent space
        osg::Vec3 _prevWorldPosition;
        osg::Vec2 _screenPosition;
        osg::Vec2 _prevScreenPosition;
        float _magnitude;        
        Widget* _widget;
        Scene*  _scene;
        //int _tapCount;
        double _time;
        //int _phase;
        TouchShape* _touchShape;  //pointer to the visualization shape
        
};



class TouchAsync {
    public:
        
        enum  Type { ENTER, DOWN, MOVE, UP, LEAVE };
        
        TouchAsync( int id, float x, float y, float magnitude, Type type )
          : _id(id),
            _x(x),
            _y(y),
            _magnitude(magnitude),
            _type(type)
        {}
        
        int getId() {return _id;}
        float getX() {return _x;}
        float getY() {return _y;}          
        float getMagnitude() {return _magnitude;}          
        Type getType() {return _type;}
        
   
    protected:
        friend class Scene;
        int _id;
        float _x;
        float _y;
        float _magnitude;
        Type _type;
};



class TouchHit {
    // this is used as a temp storage container in
    // the ray intersection routine
    public:
        
        TouchHit( Widget* widget, 
                  osg::Vec2 screenPosition,
                  osg::Vec3 localPosition,
                  osg::Vec3 worldPosition
                )
          : _widget (widget),
            _screenPosition(screenPosition),
            _position(localPosition),
            _worldPosition(worldPosition)
        {}
            
    protected:
        friend class Scene;
        Widget*   _widget;
        osg::Vec2 _screenPosition;
        osg::Vec3 _position;
        osg::Vec3 _worldPosition;    
};


}
#endif
