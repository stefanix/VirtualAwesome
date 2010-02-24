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
* Multipad is an input addon for the multitouch pad on Apple
* notebooks. It uses a psudo-singelton, construct-on-first-use idiom.
* The active instance is being made available via the getMultipad() 
* function.The main reason this is done like this is because the 
* callback from the underlying system calls needs to be a regular 
* function.To make it integrate with this class it uses a static 
* member funtion and to give this static member function access to 
* the Multipad instance it uses a globally accessable instance.
* Also see: 
* http://www.parashift.com/c++-faq-lite/ctors.html#faq-10.14
*
*/


#ifndef VAMULTIPAD_MULTIPAD
#define VAMULTIPAD_MULTIPAD

// Some system compatibility checks
//
#ifndef __APPLE_CC__
    #error This works only on OSX 10.5 and later.
#else
    #if (MAC_OS_X_VERSION_MAX_ALLOWED < MAC_OS_X_VERSION_10_5)
        #error You need OSX 10.5 or later and a multitouch trackpad.
    #endif
#endif


#include <mach/mach.h> 
#include <IOKit/IOKitLib.h> 
#include <CoreFoundation/CoreFoundation.h> 

#include <map>
#include <vector>
#include <iostream>

#include <osg/GraphicsContext>
#include <va/EventHandlers.h>


extern "C" {
    
    typedef struct { float x,y; } mtPoint;
    typedef struct { mtPoint pos,vel; } mtReadout;
    
    typedef struct {
        int frame;
        double timestamp;
        int identifier, state, foo3, foo4;
        mtReadout normalized;
        float size;
        int zero1;
        float angle, majorAxis, minorAxis; // ellipsoid
        mtReadout mm;
        int zero2[2];
        float unk2;
    } Finger;
    
    typedef int MTDeviceRef;
    typedef int (*MTContactCallbackFunction)(int,Finger*,int,double,int);
    
    MTDeviceRef MTDeviceCreateDefault();
    void MTRegisterContactFrameCallback(MTDeviceRef, MTContactCallbackFunction);
    void MTUnregisterContactFrameCallback(MTDeviceRef, MTContactCallbackFunction);
    void MTDeviceStart(MTDeviceRef);
    void MTDeviceStop(MTDeviceRef);
    void MTDeviceRelease(MTDeviceRef);
    
}



namespace vaMultipad {


class Touch {
    public:

        int id;
        float x;
        float y;
        float angle;
        float size;

        
        Touch() : id(-1), x(0), y(0), angle(0.f), size(0.f) {}
};


class Multipad {
    public:

        Multipad();
        ~Multipad();
        
        static int callback(int device, Finger *data, int nFingers,
                        double timestamp, int frame);
        
        void addEventHandler( va::RawTouchHandler* handler );
    	
        void triggerTouchEnter( int id, float x, float y, float size );
        void triggerTouchDown( int id, float x, float y, float size );
        void triggerTouchMove( int id, float x, float y, float size );
        void triggerTouchUp( int id, float x, float y, float size );
        void triggerTouchLeave( int id, float x, float y, float size );
        
                
    protected:
    	float _scaleX;
        float _scaleY;
    	MTDeviceRef _mt_device;
        std::map<int,Touch> _lastTouches;
        std::vector<va::RawTouchHandler*> _eventHandlers;
        
        Multipad(Multipad const&);
        void operator=(Multipad const&);
};


//access to Multipad Singelton
//
extern Multipad* getMultipad();


}
#endif

