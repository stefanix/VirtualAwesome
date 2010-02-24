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

#include <vaMultipad/Multipad.h>

using namespace vaMultipad;


Multipad::Multipad() {

    //get screen width, height
    unsigned int width, height;
    osg::GraphicsContext::WindowingSystemInterface* wsi = osg::GraphicsContext::getWindowingSystemInterface();
    if (!wsi) {
        osg::notify(osg::FATAL)<<"no WindowSystemInterface available"<<std::endl;
    }
    wsi->getScreenResolution(osg::GraphicsContext::ScreenIdentifier(0), width, height);
    _scaleX = static_cast<float> (width);
    _scaleY = static_cast<float> (height);
    
    _mt_device = MTDeviceCreateDefault();
    MTRegisterContactFrameCallback(_mt_device, &Multipad::callback);
    MTDeviceStart(_mt_device);
}

Multipad::~Multipad() {
    MTDeviceStop(_mt_device);
    MTUnregisterContactFrameCallback(_mt_device, &Multipad::callback);
    MTDeviceRelease(_mt_device);
    _mt_device = NULL;    
}


int Multipad::callback(int device, Finger *data, int nFingers,
                        double timestamp, int frame)
{

	Multipad* instance = getMultipad();

    for( int i=0; i<nFingers; i++ ) {
        Finger* finger = &data[i];
        
        if( instance->_lastTouches.find(finger->identifier) != instance->_lastTouches.end() ) {
        	//moved
            instance->triggerTouchMove( finger->identifier, 
                                        finger->normalized.pos.x, 
                                        finger->normalized.pos.y, 
                                        finger->size );
            
            instance->_lastTouches.erase(finger->identifier);         
        } else {
            //enter,down
            instance->triggerTouchEnter( finger->identifier, 
                                         finger->normalized.pos.x, 
                                         finger->normalized.pos.y, 
                                         finger->size );
            instance->triggerTouchDown( finger->identifier, 
                                        finger->normalized.pos.x, 
                                        finger->normalized.pos.y, 
                                        finger->size );                                                    
        }
    }

	// the remaining ids are touch leave,up events
    for( std::map<int,Touch>::const_iterator iter = instance->_lastTouches.begin();
       iter != instance->_lastTouches.end();
       ++iter )
    {
        //leave
        const Touch& touch = iter->second;
        instance->triggerTouchUp( touch.id, touch.x, touch.y, touch.size );
        instance->triggerTouchLeave( touch.id, touch.x, touch.y, touch.size );
    }
  
	// update _lastTouches
    instance->_lastTouches.clear();
    for( int i=0; i<nFingers; i++ ) {
        Finger* finger = &data[i];
        
        Touch touch;
        touch.id = finger->identifier;
        touch.x = finger->normalized.pos.x;
        touch.y = finger->normalized.pos.y;
        touch.size = finger->size;

        instance->_lastTouches[touch.id] = touch;
    }

	/*
    for (int i=0; i<nFingers; i++) {
        Finger *f = &data[i];
        printf("Frame %7d: Angle %6.2f, ellipse %6.3f x%6.3f; "
               "position (%6.3f,%6.3f) vel (%6.3f,%6.3f) "
               "ID %d, state %d [%d %d?] size %6.3f, %6.3f?\n",
           f->frame,
           f->angle * 90 / atan2(1,0),
           f->majorAxis,
           f->minorAxis,
           f->normalized.pos.x,
           f->normalized.pos.y,
           f->normalized.vel.x,
           f->normalized.vel.y,
           f->identifier, f->state, f->foo3, f->foo4,
           f->size, f->unk2);
    }
    printf("\n");
    */
    
    return 0;
}


void Multipad::addEventHandler( va::RawTouchHandler* handler ) {
    _eventHandlers.push_back(handler);
}


void Multipad::triggerTouchEnter( int id, float x, float y, float size ){
    for(unsigned int j=0; j<_eventHandlers.size(); ++j) {
        _eventHandlers[j]->rawTouchEnterAsync( id, x*_scaleX, y*_scaleY, size*30 );
    }
}
void Multipad::triggerTouchDown( int id, float x, float y, float size ){
    for(unsigned int j=0; j<_eventHandlers.size(); ++j) {
        _eventHandlers[j]->rawTouchDownAsync( id, x*_scaleX, y*_scaleY, size*30 );
    }
}
void Multipad::triggerTouchMove( int id, float x, float y, float size ){
    for(unsigned int j=0; j<_eventHandlers.size(); ++j) {
        _eventHandlers[j]->rawTouchMoveAsync( id, x*_scaleX, y*_scaleY, size*30 );
    }
}
void Multipad::triggerTouchUp( int id, float x, float y, float size ){
    for(unsigned int j=0; j<_eventHandlers.size(); ++j) {
        _eventHandlers[j]->rawTouchUpAsync( id, x*_scaleX, y*_scaleY, size*30 );
    }
}
void Multipad::triggerTouchLeave( int id, float x, float y, float size ){
    for(unsigned int j=0; j<_eventHandlers.size(); ++j) {
        _eventHandlers[j]->rawTouchLeaveAsync( id, x*_scaleX, y*_scaleY, size*30 );
    }
}


//access to Multipad Singelton
//
Multipad* vaMultipad::getMultipad(){
    static Multipad* instance = new Multipad();
    return instance;
} 

