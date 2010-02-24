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
* The Scene is one of the most central classes.
* It embodies the viewer, camera, and scene graph root.
* Per application there is usually one instance as part of
* the App derived class of which there is one instance in main().
* Scene and App work together. All the standard events
* (mouse, keyboard, resize) are send from the scene's viewer to
* the App. Latter being the super global, grand-central-like
* event handler and where (the subclass of App) all the user 
* code goes.
*
*/

#ifndef VA_SCENE
#define VA_SCENE

#include <stack>

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/MatrixTransform>
#include <osgViewer/Viewer>
#include <osg/Math>
#include <osg/Vec3>

#include <va/Constants.h>
#include <va/Types.h>
#include <va/EventHandlers.h>
#include <va/Key.h>
#include <va/Mouse.h>
#include <va/Pen.h>
#include <va/Touch.h>
#include <va/GuiEvents.h>
#include <va/Visitors.h>
#include <va/Node.h>
#include <va/TouchShape.h>

#ifdef TARGET_OSX
#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>
#endif


namespace va {


class App;
class Node;
class Widget;



class Scene : public Node, 
              public KeyHandler, 
              public MouseHandler, 
              public RawTouchHandler {
              
    public:
      
        Scene();
        virtual ~Scene();

        int run();
        
        void addUpdateHandler( UpdateHandler* handler ); 
        void addResizeHandler( ResizeHandler* handler );      
        void addKeyHandler( KeyHandler* handler );
        void addMouseHandler( MouseHandler* handler );
        void addPenHandler( PenHandler* handler );      
        void addTouchHandler( TouchHandler* handler );      
        
        
        // Accessors
        //    
        int getWidth() { return _width; }
        int getHeight() { return _height; }
        void setBackgroundColor( const osg::Vec4& color );
        void setBackgroundColor( float r, float g, float b, float a=1.0f );
        const osg::Vec4& getBackgroundColor();
        void setBackgroundAuto( bool bAuto );
        int getFrameNumber();
        double getSimulationTime();  //in sec from app launch
        
        
        // enablers/disablers
        void enableDefaultLighting();
        void disableDefaultLighting();
        void enableMultisampling( int val=4 );
        void disableMultisampling();       
        
        
        // Cursor stuff
        //
        //void warpCursor( float x, float y );  //reposition
        void showCursor();
        void hideCursor();
        void enableTouchVisuals( int maxNum=25 );  //for multitouch
		void disableTouchVisuals();                //for multitouch


        // Inject Key Events
        //
        void keyPress( Key& key );
        void keyRelease( Key& key );


        // Inject Mouse Events
        //
        void mouseButton( Mouse& mouse );
        void mouseScroll( Mouse& mouse );

                
        // Inject Touch Events
        //        
        void rawTouchEnter( int id, int x, int y, float magnitude );
        void rawTouchDown( int id, int x, int y, float magnitude );
        void rawTouchMove( int id, int x, int y, float magnitude );
        void rawTouchUp( int id, int x, int y, float magnitude );
        void rawTouchLeave( int id, int x, int y, float magnitude );


        // Inject Asynchronous Touch Events
        // Use these when called from another thread.
        //        
        void rawTouchEnterAsync( int id, int x, int y, float magnitude );
        void rawTouchDownAsync( int id, int x, int y, float magnitude );
        void rawTouchMoveAsync( int id, int x, int y, float magnitude );
        void rawTouchUpAsync( int id, int x, int y, float magnitude );
        void rawTouchLeaveAsync( int id, int x, int y, float magnitude );
                
              
        // OSG stuff
        //
        osg::ref_ptr<osg::Camera> getOsgCamera() { return _camera; }
        void toggleStats() {_viewer->getEventQueue()->keyPress(_statsKey);}    
                
    
    protected:
    	friend class GuiEvents;
        
        osg::ref_ptr<GuiEvents> _guiEvents;
                
        unsigned int _width, _height;
        bool _bUseCursor;
        bool _bKioskMode;
        int _maxFrameRate;
        int _statsKey;
        
        osg::ref_ptr<osgViewer::Viewer>               _viewer;
        osg::ref_ptr<osgViewer::GraphicsWindow>       _window;
        osg::ref_ptr<osg::GraphicsContext::Traits>    _traits;
        osg::ref_ptr<osg::Camera>                     _camera;
        osg::ref_ptr<osgViewer::StatsHandler>         _statsHandler;
                        
        std::map<int,Touch*>  _activeTouches;  // active touches by id, map owns the objects
        std::map<int,TouchHit*>  _touchHits;   // intermediary touches, sorted by zIndex
        std::stack<TouchShape*>  _touchShapePool;       // reusable TouchShape's
        std::map<int,TouchShape*>  _activeTouchShapes;  // uses TouchShape's from the Stack
        std::vector<TouchHandler*> _touchHandlers;
        
        std::vector<TouchAsync*>  _asyncTouches;        // these are touches coming in through the async injection calls
        OpenThreads::Mutex _asyncTouchesMutex;
        
        zIndexWidgetVisitor  _zIndexVisitor;     // Scene graph visitor, see OSG visitor pattern.
                                                 // Sets the zIndex according to graph hierachy.
                                                 
        void setupPixelCamera();
        void setupLookAtCamera();                                                              
        void zIndexWidgetTraversal();
        void handleMultimouseEvents();
        void rayIntersectWidgets( float x, float y );
        osg::Vec3d  rayIntersectWithXYPlane(float x, float y, Widget* widget);
        bool getPlaneLineIntersection(const osg::Vec4d& plane, 
                                      const osg::Vec3d& lineStart, const osg::Vec3d& lineEnd, 
                                      osg::Vec3d& isect);    
        
        virtual void touchDown( Touch* touch );
        virtual void touchMove( Touch* touch );
        virtual void touchUp( Touch* touch );
};


}
#endif

