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

#ifndef VAMICE_MICE
#define VAMICE_MICE

#include <map>
#include <vector>
#include <osg/Notify>
#include <osg/GraphicsContext>
#include <manymouse.h>
#include <va/Mouse.h>
#include <va/EventHandlers.h>

namespace vaMice {


class Mice {
    public:

        Mice();
        ~Mice();

        void update();
        void addEventHandler( va::RawTouchHandler* handler );
        
        
    protected:
    	bool _bInitiated;
    	unsigned int _width;
        unsigned int _height;
        std::map<int,va::Mouse*>  _activeMultimouses; 
        std::vector<va::RawTouchHandler*> _eventHandlers; 
    
};


}
#endif

