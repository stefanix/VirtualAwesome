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

#include <osgDB/ReaderWriter>
#include <osgDB/FileUtils>

#include <va/Scene.h>
#include <va/App.h>
#include <va/Node.h>
#include <va/Shape.h>
#include <va/Widget.h>	

using namespace va;


Scene::Scene() {
    _bUseCursor = true;
    _bKioskMode = true;
    _maxFrameRate = 60;
    _statsKey = 60000;

    // create the viewer of the scene.
    _viewer = new osgViewer::Viewer;
    //_viewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);
    _viewer->setUpViewOnSingleScreen(0);
    
    // get the GraphicsWindow, make available as member
    osgViewer::Viewer::Windows windows; 
    _viewer->getWindows(windows);
    _window = windows.at(0);   
    
    // get width and height of the graphics context
    osg::GraphicsContext::WindowingSystemInterface* wsi = osg::GraphicsContext::getWindowingSystemInterface();
    if (!wsi) { osg::notify(osg::FATAL)<<"no WindowSystemInterface available"<<std::endl; }
    wsi->getScreenResolution(osg::GraphicsContext::ScreenIdentifier(0), _width, _height);    
    
    // create a root node for the scene
    _xform->setName("scene");
    _viewer->setSceneData(_xform.get());

	// stats handler
    _statsHandler = new osgViewer::StatsHandler();
    _statsHandler->setKeyEventTogglesOnScreenStats(_statsKey);
    _statsHandler->setKeyEventPrintsOutStats(_statsKey+1);
    _viewer->addEventHandler(_statsHandler);
    
	// handel events from GuiEvents
    // which dispatches events from the viewer
    _guiEvents = new GuiEvents();
    _guiEvents->_scene = this;
    _viewer->addEventHandler(_guiEvents.get());
    addKeyHandler(this);    // so the scene can delegate keys to widgets
    addMouseHandler(this);  // so the scene can delegate button/scoll
    
    // Establish mouse pointer as touch.
    // This is necessary because the mouse is treated like any other touch.
    // Touches do the following: 'enter', 'down', 'move', 'up', 'leave'
    // The mouse events maps to touch events like this:
    // press -> down, move -> move, drag -> move, release -> up
    if (_bUseCursor) {
        rawTouchEnter(_guiEvents->_mouseEvent.getId(),
                      _guiEvents->_mouseEvent.getX(),
                      _guiEvents->_mouseEvent.getY(), 1.0);
    }    
        
    // get the master camera and set it up
    _camera = _viewer->getCamera();
    setupPixelCamera();

    setBackgroundColor(0.1568, 0.1804, 0.2431);

    // anti-alias by default
    // osg::DisplaySettings::instance()->setNumMultiSamples(4);

    // default lights but disable lighting
    enableDefaultLighting();
    disableLighting();
    
    //hide system UIs, kiosk mode via SetSystemUIMode
    //http://developer.apple.com/mac/library/technotes/tn2002/tn2062.html
    //SetSystemUIMode(kUIModeAllHidden, NULL);


    osgDB::FilePathList& dataFilePathList = osgDB::getDataFilePathList();
    dataFilePathList.push_back("../../data/");     // OSX cmake bundle, VS9
    dataFilePathList.push_back("data/");
    dataFilePathList.push_back("../data/");
    dataFilePathList.push_back("../../../data/");
    dataFilePathList.push_back("../../../../data/");       // global
    dataFilePathList.push_back("../../../../../data/");    // global, OSX cmake bundle, VS9
    dataFilePathList.push_back("../../../../../../data/"); // global
    osgDB::setDataFilePathList(dataFilePathList);
    //std::cout << "dataFilePathList" << std::endl;
    //for( unsigned int i=0; i<dataFilePathList.size(); i++ ) {
    //    std::cout << dataFilePathList[i] << std::endl;
    //}

}


Scene::~Scene() {
    // end life cycle of the mouse as a touch
    if (_bUseCursor) {
        rawTouchLeave(_guiEvents->_mouseEvent.getId(),
                      _guiEvents->_mouseEvent.getX(),
                      _guiEvents->_mouseEvent.getY(), 1.0);
    }    
}


void Scene::setupPixelCamera() {
    //set up the camera so one pixel is one unit

    double halfFov, theTan, screenFov, aspect;
    screenFov 		= 45.0;

    double eyeX 	 = (double)_width / 2.0;
    double eyeY 	 = (double)_height / 2.0;
    halfFov 		 = osg::PI * screenFov / 360.0;
    theTan 			 = tanf(halfFov);
    double dist 	 = eyeY / theTan;
    double nearDist  = dist / 10.0;	  // near/far clip plane
    double farDist 	 = dist * 10.0;
    aspect 			 = (double)_width/(double)_height;

    _camera->setProjectionMatrixAsPerspective(screenFov, aspect, nearDist, farDist);
    _camera->setViewMatrixAsLookAt(osg::Vec3d(eyeX, eyeY, dist),  //cam pos
                                   osg::Vec3d(eyeX, eyeY, 0.0),   //look at pos
                                   osg::Vec3d(0.0, 1.0, 0.0));    //up vector

    // Origin
    // The origin is at the bottom left, X-axis is left to right
    // Y-axis bottom to top, Z-axis is into the screen.
    // This is consisten with OSG and OpenGL.
    // Fllip y axis is possible with the following lines but be warned
    // this does not flip anything texture based like text.
    // root->setScale(osg::Vec3(1.0,-1.0,1.0));
    // root->setPosition(osg::Vec3(0.0,h,0.0));

    // Clipping Planes
    // by default near and far clipping planes are auto-computed
    // based on the global bounding sphere, in rare cases it might
    // be necessary to switch this off with the following line
    // camera->setComputeNearFarMode(osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR);
}

void Scene::setupLookAtCamera() {
    //camera->setViewMatrixAsLookAt (const osg::Vec3d &eye, const osg::Vec3d &center, const osg::Vec3d &up);
}


int Scene::run() {
    // this is very similar to calling viewer->run()
    // without adding a default TackballManipulator
    // this is extracted from Viewer:run() and ViewerBase::run()
    _viewer->setReleaseContextAtEndOfFrameHint(false);

    if (!_viewer->isRealized()) {
        _viewer->realize();
    }

    // run simulation loop
    while (!_viewer->done()) {
        osg::Timer_t startFrameTick = osg::Timer::instance()->tick();

        if (!_bUseCursor) {
            _window->useCursor(false);
        }
        
        if (_bKioskMode) {
            #ifdef TARGET_OSX
            SetSystemUIMode(kUIModeAllHidden, NULL);
            #endif
        }

        // extracted from viewer->frame()
        if (_viewer.valid()) {

            // This traversal makes sure zIndex is set in the order
            // of rendering (depth-first traversal) for all widgets
            _zIndexVisitor.reset(0);
            _xform->accept(_zIndexVisitor);

            _viewer->advance();
            _viewer->eventTraversal();
            
            //handle asynchronous rawTouches, resync!
            _asyncTouchesMutex.lock();
            for( unsigned int i=0; i< _asyncTouches.size(); ++i ){
                va::TouchAsync* touch = _asyncTouches[i];
                switch (touch->_type) {
                    case TouchAsync::ENTER:
                        rawTouchEnter(touch->_id, touch->_x, touch->_y, touch->_magnitude);
                        break;
                    case TouchAsync::DOWN:
                        rawTouchDown(touch->_id, touch->_x, touch->_y, touch->_magnitude);
                        break;
                    case TouchAsync::MOVE:
                        rawTouchMove(touch->_id, touch->_x, touch->_y, touch->_magnitude);
                        break;
                    case TouchAsync::UP:
                        rawTouchUp(touch->_id, touch->_x, touch->_y, touch->_magnitude);
                        break;
                    case TouchAsync::LEAVE:
                        rawTouchLeave(touch->_id, touch->_x, touch->_y, touch->_magnitude);
                        break;                                                                        
                    default:
                        break;
                }
                delete touch;
            }
            _asyncTouches.clear();
            _asyncTouchesMutex.unlock();            
            
            for(unsigned int i=0; i<_guiEvents->_updateHandlers.size(); ++i) {
                _guiEvents->_updateHandlers[i]->update();
            }
                    
            _viewer->updateTraversal();
            
            
        }

        
        if (_viewer.valid()) {
            _viewer->renderingTraversals();
        }
        
        // work out if we need to force a sleep to hold back the frame rate 
        osg::Timer_t endFrameTick = osg::Timer::instance()->tick(); 
        double frameTime = osg::Timer::instance()->delta_s(startFrameTick, endFrameTick);
        double minFrameTime = _maxFrameRate>0.0 ? 1.0/_maxFrameRate : 0.0; 
        if (frameTime < minFrameTime) {
			OpenThreads::Thread::microSleep(1000000.0*(minFrameTime-frameTime));
        }
    }

    return 0;
}



void Scene::addUpdateHandler( UpdateHandler* handler ){
    _guiEvents->addUpdateHandler(handler);
}
void Scene::addResizeHandler( ResizeHandler* handler ){
	_guiEvents->addResizeHandler(handler);
}

void Scene::addKeyHandler( KeyHandler* handler ){
	_guiEvents->addKeyHandler(handler);
}
void Scene::addMouseHandler( MouseHandler* handler ){
	_guiEvents->addMouseHandler(handler);
}
void Scene::addPenHandler( PenHandler* handler ){
	_guiEvents->addPenHandler(handler);
}
void Scene::addTouchHandler( TouchHandler* handler ){
	_touchHandlers.push_back(handler);
}




// Accesssors
//

void Scene::setBackgroundColor( const osg::Vec4& color ) {
    _camera->setClearColor(color);
}
void Scene::setBackgroundColor( float r, float g, float b, float a ) {
    setBackgroundColor(osg::Vec4(r,g,b,1.0));
}

const osg::Vec4& Scene::getBackgroundColor() {
    return _camera->getClearColor();
}

void Scene::setBackgroundAuto( bool bAuto ) {
    if( bAuto ) {
        _camera->setClearMask( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    } else {
        _camera->setClearMask(0);
    }
}

int Scene::getFrameNumber() {
    return _viewer->getViewerFrameStamp()->getFrameNumber();
}

double Scene::getSimulationTime() {
    return _viewer->getViewerFrameStamp()->getSimulationTime();
}



// enablers/disablers
//

void Scene::enableDefaultLighting() {
    _viewer->setLightingMode(osg::View::SKY_LIGHT);
}
void Scene::disableDefaultLighting() {
    _viewer->setLightingMode(osg::View::NO_LIGHT);
}

void Scene::enableMultisampling( int val ) {
    osg::DisplaySettings::instance()->setNumMultiSamples(val);
}
void Scene::disableMultisampling() {
    osg::DisplaySettings::instance()->setNumMultiSamples(0);
}




// Cursor stuff
//
//void Scene::warpCursor( float x, float y ) {
//	_window->requestWarpPointer(x,y);
//}
void Scene::showCursor() {
	//There is an issue in OSX/Carbon with the following 
    //call not being permanent.
    //_window->useCursor(true);
    //For this reason we use a switch and execute the previous
    //in the update continuously based on it.
    
    if (!_bUseCursor) {
        _bUseCursor = true;
        rawTouchEnter(_guiEvents->_mouseEvent.getId(),
                      _guiEvents->_mouseEvent.getX(), 
                      _guiEvents->_mouseEvent.getY(), 1.0);
    }
}
void Scene::hideCursor() {
	//There is an issue in OSX/Carbon with the following 
    //call not being permanent.
    //_window->useCursor(false);
    //For this reason we use a switch and execute the previous
    //in the update continuously based on it.
    
    if (_bUseCursor) {
        _bUseCursor = false;
        rawTouchLeave(_guiEvents->_mouseEvent.getId(), 
                      _guiEvents->_mouseEvent.getX(), 
                      _guiEvents->_mouseEvent.getY(), 1.0);
    }
    
}

void Scene::enableTouchVisuals( int maxNum ){
    for(int i=0; i<maxNum; ++i) {
        va::TouchShape* b = new va::TouchShape();
        _touchShapePool.push(b);
        addChild( b );
        b->setVisible(false);
    }
    
    //if we already have active touches, setup shapes for them
    for( std::map<int,Touch*>::const_iterator iter = _activeTouches.begin();
       iter != _activeTouches.end();
       ++iter )
    {
        Touch* touch = iter->second;
        TouchShape* touchShape = _touchShapePool.top();
        _touchShapePool.pop();            
        touchShape->setVisible(true);
        touchShape->setPosition(touch->getScreenX(), touch->getScreenY(), 0);
        touchShape->setRadius(touch->getMagnitude());
        touchShape->setText(touch->getId());
        _activeTouchShapes[iter->first] = touchShape;
    }
    
}
void Scene::disableTouchVisuals(){
    while (_touchShapePool.size() > 0) {
    	va::TouchShape* b = _touchShapePool.top();
        _touchShapePool.pop();
    	removeChild(b);
        delete b;
    }
}




// Inject Key Events
//        
void Scene::keyPress( Key& key ){
    KeyHandler* keyHandler = FirstKeyHandler::get();
    if (keyHandler) {
        keyHandler->keyPress(key);
    }
    //TODO: if keyPress returns false traverse up
}
void Scene::keyRelease( Key& key ){
    KeyHandler* keyHandler = FirstKeyHandler::get();
    if (keyHandler) {
        keyHandler->keyRelease(key);
    }
    //TODO: if keyRelease returns false traverse up
}
        



// Inject Mouse Events
//
void Scene::mouseButton( Mouse& mouse ){
    // delegate mouse button event to the widget
    
    // check if we really have this touch
    if( _activeTouches.find(mouse.getId()) == _activeTouches.end() ) {
        osg::notify(osg::WARN) << "in mouseButton(...), invalid id" << std::endl;
    } else {
    	Touch* touch = _activeTouches[mouse.getId()];
        if (touch->_widget) {
            touch->_widget->mouseButton(mouse);
        }
    }
}
void Scene::mouseScroll( Mouse& mouse ){
	// delegate to widgets
    // calclulate intersection
    // by shooting a ray from the mouse location through the scene
    rayIntersectWidgets(mouse.getX(), mouse.getY());  //populate touchHits
    // widget with highest zIndex first
    std::map<int,TouchHit*>::reverse_iterator iter;
    for( iter = _touchHits.rbegin(); iter != _touchHits.rend(); ++iter ) {
        Widget* widget = iter->second->_widget;
        widget->mouseScroll(mouse);
		break;
    }    
}




// Inject Touch Events
//

void Scene::rawTouchEnter( int id, int x, int y, float magnitude ) {
    // check if touch is really new
    if( _activeTouches.find(id) != _activeTouches.end() ) {
        osg::notify(osg::WARN) << "in rawTouchEnter(...), id collision" << std::endl;
    } else {
        // create touch
        Touch* touch = new Touch(id, x, y, magnitude);
        //touch->_screenPosition.set(x,y);
        //touch->_prevScreenPosition.set(x,y);
        touch->_time = getSimulationTime();
        _activeTouches[id] = touch;
        touch->_scene = this;

        // setup touchShape, take from pool
        // NOTE: there is a second place setting them up: enableTouchVisuals
        if (_touchShapePool.size() > 0) {
            TouchShape* touchShape = _touchShapePool.top();
            _touchShapePool.pop();            
            touchShape->setVisible(true);
            touchShape->setPosition(x, y, 0);
            touchShape->setRadius(magnitude);
            touchShape->setText(id);
            touchShape->setDownMode(false);
            _activeTouchShapes[id] = touchShape;
            // make shape available in handlers
            touch->_touchShape = touchShape;
        }
    }
}
void Scene::rawTouchDown( int id, int x, int y, float magnitude ) {
    // check if we really have this touch
    if( _activeTouches.find(id) == _activeTouches.end() ) {
        osg::notify(osg::WARN) << "in touchDown(...), invalid id, was rawTouchEnter(...) previously called?" << std::endl;
    } else {
        // match touch
        Touch* touch = _activeTouches[id];
        touch->_prevScreenPosition = touch->_screenPosition;
        touch->_screenPosition.set(x,y);
        touch->_magnitude = magnitude;
        touch->_time = getSimulationTime();
        
        for(unsigned int i=0; i<_touchHandlers.size(); ++i) {
            _touchHandlers[i]->touchDown(*touch);
        }    
                    
        // delegate touchDown to relevant widgets
        touchDown(touch);
        
        // move touchShape
        if( _activeTouchShapes.find(id) != _activeTouchShapes.end() ) {
            TouchShape* touchShape = _activeTouchShapes[id];            
            touchShape->setPosition(x, y, 0);
            touchShape->setRadius(magnitude);
            touchShape->setDownMode(true);
        }
    }
}
void Scene::touchDown( Touch* touch ) {
    // calclulate intersection
    // by shooting a ray from the mouse location through the scene
    rayIntersectWidgets(touch->getScreenX(), touch->getScreenY());  //populate touchHits
    // call node's event handler
    // widget with highest zIndex first
    std::map<int,TouchHit*>::reverse_iterator iter;
    for( iter = _touchHits.rbegin(); iter != _touchHits.rend(); ++iter ) {
        touch->_widget = iter->second->_widget;

        // We already have an intersection point in here:
        // -----------------------------------------------------
        // touch->setLocalPosition(iter->second->localPosition);
        // touch->setWorldPosition(iter->second->worldPosition);
        // -----------------------------------------------------
        // Unfortunately this isec point is slightly different from
        // what we get with simple plane intersection, latter being
        // less accurate. Still it's more important to be conistent
        // otherwise we get a slight bump when dragging widgets.
        // For this reason we recaclulate the isec point with the
        // same method as we will be using in touchMove, touchUp.
        // Intersect touch with the associated widget's plane (x-y plane).
        osg::Vec3d isect = rayIntersectWithXYPlane(touch->getScreenX(),
                                                   touch->getScreenY(),
                                                   touch->_widget);
        touch->_position.set(isect);
        touch->_prevPosition.set(isect);

        // Call touch event handler on the first widget hit.
        // If the widget is configured to not handle touch 
        // events the second widget hit gets notified.
        if( touch->_widget->getTouchEventsEnabled()) {
            // for convenience, also store touch position in relation to the
            // widget's world coordinates (this is the parent space)
            touch->_worldPosition = touch->_position * touch->_widget->getTransform();
            touch->_prevWorldPosition = touch->_worldPosition;        
        
            touch->_widget->touchDownInternal( *touch );
            break;
        }
    }
}




void Scene::rawTouchMove( int id, int x, int y, float magnitude ) {
    // check if we really have this touch
    if( _activeTouches.find(id) == _activeTouches.end() ) {
        osg::notify(osg::WARN) << "in touchMove(...), invalid id" << std::endl;
    } else {
        // match touch
        Touch* touch = _activeTouches[id];
        touch->_prevScreenPosition = touch->_screenPosition;
        touch->_screenPosition.set(x,y);
        touch->_magnitude = magnitude;
        touch->_time = getSimulationTime();
        
        for(unsigned int i=0; i<_touchHandlers.size(); ++i) {
            _touchHandlers[i]->touchMove(*touch);
        } 
                
        // delegate touchMove to relevant widgets
        touchMove(touch);
        
        // move touchShape
        if( _activeTouchShapes.find(id) != _activeTouchShapes.end() ) {
            TouchShape* touchShape = _activeTouchShapes[id];            
            touchShape->setPosition(x, y, 0);
            touchShape->setRadius(magnitude);
        }        
    }
}
void Scene::touchMove( Touch* touch ) {
    if( touch->_widget ) {
        // Intersect touch with the associated widget's plane (x-y plane).
        osg::Vec3d isect = rayIntersectWithXYPlane(touch->getScreenX(),
                                                   touch->getScreenY(),
                                                   touch->_widget);
                                                   
        touch->_prevPosition = touch->_position;                                           
        touch->_position.set(isect);
        
        // for convenience, also store touch position in relation to the
        // widget's world coordinates (this is the parent space)
        touch->_prevWorldPosition = touch->_worldPosition;
        touch->_worldPosition = touch->_position * touch->_widget->getTransform();        
        
        touch->_widget->touchMoveInternal( *touch );
    }
}




void Scene::rawTouchUp( int id, int x, int y, float magnitude ) {
    // check if we really have this touch
    if( _activeTouches.find(id) == _activeTouches.end() ) {
        osg::notify(osg::WARN) << "in rawTouchUp(...), invalid id" << std::endl;
    } else {
        // match touch
        Touch* touch = _activeTouches[id];
        touch->_prevScreenPosition = touch->_screenPosition;
        touch->_screenPosition.set(x,y);
        touch->_magnitude = magnitude;
        touch->_time = getSimulationTime();

        for(unsigned int i=0; i<_touchHandlers.size(); ++i) {
            _touchHandlers[i]->touchUp(*touch);
        } 
        
        // delegate touchUp to relevant widgets
        touchUp(touch);

        // move touchShape
        if( _activeTouchShapes.find(id) != _activeTouchShapes.end() ) {
            TouchShape* touchShape = _activeTouchShapes[id];            
            touchShape->setPosition(x, y, 0);
            touchShape->setRadius(magnitude);
            touchShape->setDownMode(false);
        }        
    }
}
void Scene::touchUp( Touch* touch ) {
    if( touch->_widget ) {
        // Intersect touch with the associated widget's plane (x-y plane).
        osg::Vec3d isect = rayIntersectWithXYPlane(touch->getScreenX(),
                                                   touch->getScreenY(),
                                                   touch->_widget);

        touch->_prevPosition = touch->_position;                                           
        touch->_position.set(isect);
        
        // for convenience, also store touch position in relation to the
        // widget's world coordinates (this is the parent space)
        touch->_prevWorldPosition = touch->_worldPosition;
        touch->_worldPosition = touch->_position * touch->_widget->getTransform();
                                       
        touch->_widget->touchUpInternal( *touch );                                                   
    }
}
void Scene::rawTouchLeave( int id, int x, int y, float magnitude ) {
    // check if we really have this touch
    if( _activeTouches.find(id) == _activeTouches.end() ) {
        osg::notify(osg::WARN) << "in rawTouchLeave(...), invalid id" << std::endl;
    } else {
        // remove touch
        delete _activeTouches[id];        
        _activeTouches.erase(id);
        
        // 'remove' touchShape, hide and put back into the pool for reuse
        if( _activeTouchShapes.find(id) != _activeTouchShapes.end() ) {
            TouchShape* touchShape = _activeTouchShapes[id];
            touchShape->setVisible(false);
            _touchShapePool.push(touchShape);
            _activeTouchShapes.erase(id);
        }         
    }
}



// Inject Asynchronous Touch Events
// Use these when called from another thread.
// The events will be resynced with the main thread.
//     
void Scene::rawTouchEnterAsync( int id, int x, int y, float magnitude ){
	_asyncTouchesMutex.lock();
	_asyncTouches.push_back(new TouchAsync(id,x,y,magnitude,TouchAsync::ENTER));
    _asyncTouchesMutex.unlock();
}
void Scene::rawTouchDownAsync( int id, int x, int y, float magnitude ){
	_asyncTouchesMutex.lock();
	_asyncTouches.push_back(new TouchAsync(id,x,y,magnitude,TouchAsync::DOWN));
    _asyncTouchesMutex.unlock();
}
void Scene::rawTouchMoveAsync( int id, int x, int y, float magnitude ){
	_asyncTouchesMutex.lock();
	_asyncTouches.push_back(new TouchAsync(id,x,y,magnitude,TouchAsync::MOVE));
    _asyncTouchesMutex.unlock();
}
void Scene::rawTouchUpAsync( int id, int x, int y, float magnitude ){
	_asyncTouchesMutex.lock();
	_asyncTouches.push_back(new TouchAsync(id,x,y,magnitude,TouchAsync::UP));
    _asyncTouchesMutex.unlock();
}
void Scene::rawTouchLeaveAsync( int id, int x, int y, float magnitude ){
	_asyncTouchesMutex.lock();
	_asyncTouches.push_back(new TouchAsync(id,x,y,magnitude,TouchAsync::LEAVE));
    _asyncTouchesMutex.unlock();
}
        
        



// Private Methods
//

void Scene::rayIntersectWidgets( float x, float y ) {
    // return the widget node that is under the x,y screen position
    // for multiple hits return closest to the camera
    // for no hits return NULL

    // clear touchHits
    std::map<int,TouchHit*>::iterator iter;
    for( iter = _touchHits.begin(); iter != _touchHits.end(); ++iter ) {
        delete iter->second;
    }
    _touchHits.clear();

    osgUtil::LineSegmentIntersector::Intersections intersections;
    if( _viewer->computeIntersections(x,y,intersections) ){
        osgUtil::LineSegmentIntersector::Intersections::iterator  hitr;
        for(hitr = intersections.begin(); hitr != intersections.end(); ++hitr) {
            if (!hitr->nodePath.empty()) {
                osg::Referenced* node = hitr->nodePath.back()->getUserData();
                Widget* widget = dynamic_cast<Widget*>(node);
                if( widget ) {
                    TouchHit* touchHit = new TouchHit(
                        widget, osg::Vec2(x,y),
                        hitr->getLocalIntersectPoint(),
                        hitr->getWorldIntersectPoint()
                    );
                    _touchHits[widget->getZIndex()] = touchHit;
                }
            }
        }
    }
}


osg::Vec3d  Scene::rayIntersectWithXYPlane(float x, float y, Widget* widget) {
    // flip mouse y axis, only needed when embedded in glut (legecy)
    // y = height - y;

    osg::Vec3d isect = osg::Vec3d(0.0, 0.0, 0.0);

    // compute model to window transform
    // Model*View*Projection*WindowMatrix
    osg::Matrixd matrix;
    matrix.postMult(widget->getWorldTransform());
    matrix.postMult(_camera->getViewMatrix());
    matrix.postMult(_camera->getProjectionMatrix());
    matrix.postMult(_camera->getViewport()->computeWindowMatrix());

    osg::Matrixd inverse;
    inverse.invert(matrix);

    // Transform ray from window to model coordinates
    osg::Vec3d startRay = osg::Vec3d(x, y, 0.0) * inverse;
    osg::Vec3d endRay = osg::Vec3d(x, y, 1.0) * inverse;

    // Intersect ray with XY-plane
    // (0,0,1,0) is plane in hess normal form
    getPlaneLineIntersection(osg::Vec4d(0.0, 0.0, 1.0, 0.0), startRay, endRay, isect);

    return isect;
}
bool Scene::getPlaneLineIntersection(const osg::Vec4d& plane,
                                     const osg::Vec3d& lineStart, const osg::Vec3d& lineEnd,
                                     osg::Vec3d& isect)
{
    // intersects an infinite line with an infinite plane
    // in hesse normal form  Ax + By + Cz + D = 0
    // A,B,C is the normal vector of the plane, D the distance to the origin
    const double deltaX = lineEnd.x() - lineStart.x();
    const double deltaY = lineEnd.y() - lineStart.y();
    const double deltaZ = lineEnd.z() - lineStart.z();

    const double denominator = (plane[0]*deltaX + plane[1]*deltaY + plane[2]*deltaZ);
    if (! denominator) return false;

    const double C = (plane[0]*lineStart.x() + plane[1]*lineStart.y() + plane[2]*lineStart.z() + plane[3]) / denominator;

    isect.x() = lineStart.x() - deltaX * C;
    isect.y() = lineStart.y() - deltaY * C;
    isect.z() = lineStart.z() - deltaZ * C;

    return true;
}




