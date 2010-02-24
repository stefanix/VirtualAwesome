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

#ifndef VA_WIDGET
#define VA_WIDGET

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Material>
#include <osg/Vec3>
#include <osg/MatrixTransform>
#include <osgText/Text>
#include <osg/LineWidth>

#include <va/Constants.h>
#include <va/Types.h>
#include <va/Node.h>
#include <va/VertexGeometry.h>
#include <va/EventHandlers.h>
#include <va/Touch.h>
#include <va/Visitors.h>

namespace va {


class Widget : public Node, 
               public KeyHandler,
               public TouchHandler, 
               public MouseHandler {

    public:  
      
        Widget();
        virtual void reshape( float w, float h );           
        virtual void reshape() {}
        
        virtual void setWidth( float w );
        virtual float getWidth() {return _width;}
        virtual void setHeight( float h );
        virtual float getHeight() {return _height;}

        virtual void setName( const std::string& name);
        virtual const std::string& getName();
        virtual void setZIndex(long zIndex);
        virtual long getZIndex();
                        
        virtual void setBackgroundColor( float r, float g, float b, float a );
        virtual void setBackgroundColor( const osg::Vec4& color );
        virtual const osg::Vec4& getBackgroundColor();
        virtual void setBorderColor( float r, float g, float b, float a );
        virtual void setBorderColor( const osg::Vec4& color );
        virtual const osg::Vec4& getBorderColor();         
            
        virtual void setXY( const osg::Vec3& pnt ); // convinience method for setting pos in the x,y plane
        virtual void addXY( const osg::Vec3& pnt ); // convinience method for adding to pos in the x,y plane      
        virtual void setPosition( float x, float y, float z=0.0f);
        using Node::setPosition;
                
        bool isDragging(Touch& touch);
        const osg::Vec3& getDragDelta( Touch& touch );
        const osg::Vec3& getWorldDragDelta( Touch& touch ); 

        virtual void update() {}
        
        virtual void touchDown( Touch& touch );
        virtual void touchMove( Touch& touch );
        virtual void touchUp( Touch& touch );
        
        virtual void mouseButton( Mouse& mouse ) {}
        virtual void mouseScroll( Mouse& mouse ) {}      
        
        void enableTouchEvents();
        void disableTouchEvents();
        bool getTouchEventsEnabled() {return _bTouchEventsEnabled;}
        
        // Focus behavior of the widget.
        // For the WidgetFocusVisitor this typically means
        // the widget and any widget up the hierarchy is traversed
        // on a touchDown event. Any widget that returns true on 
        // wantsToFrontOnTouch() is brought to the front and the 
        // first widget that returns true on wantsKeyFocusOnTouch() 
        // becaomes the first key handler. See WidgetFocusVisitor.
        virtual bool wantsToFrontOnTouch() {return false;} 
        virtual bool wantsKeyFocusOnTouch() {return false;}
                        
      
    protected:
      	friend class Scene;
        friend class WidgetTouchEventVisitor;
        
        osg::ref_ptr<VertexGeometry> _background;
        osg::ref_ptr<VertexGeometry> _border;
        
        // width, height are the reference bounds
        // they are not clipping bounds by any means
        // reshape() determines how to interpret them
        float _width;
        float _height;

        long _zIndex;
        std::map<int,Touch*>  _activeTouches;
        std::map<Touch*,osg::Vec3>  _touchDownLocalPosition;  //keep track where the touch came
        std::map<Touch*,osg::Vec3>  _lastLocalPosition;       //keep track of previous hits, by touch
        
        osg::Vec3 _dragDelta;
        osg::Vec3 _worldDragDelta;
        
        WidgetFocusVisitor  _widgetFocusVisitor;  //used in touchDownInternal

        void touchDownInternal( Touch& touch );
        void touchMoveInternal( Touch& touch );
        void touchUpInternal( Touch& touch );
        bool _bTouchEventsEnabled;  
        bool _bTouchEventsEnabledSticky;  
        
        float rangemap(float r1val, float r1min, float r1max, float r2min, float r2max);

};


}
#endif