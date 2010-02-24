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

#include <vaMice/Mice.h>

using namespace vaMice;


Mice::Mice() {
	
    //get screen width, height
    osg::GraphicsContext::WindowingSystemInterface* wsi = osg::GraphicsContext::getWindowingSystemInterface();
    if (!wsi) {
        osg::notify(osg::FATAL)<<"no WindowSystemInterface available"<<std::endl;
    }
    wsi->getScreenResolution(osg::GraphicsContext::ScreenIdentifier(0), _width, _height);    
    
    int num = ManyMouse_Init();
    if (num <= 0) {
    	osg::notify(osg::NOTICE)
        	<< "in enableMultimouse(), no mouse devices detected!" 
            << std::endl;
    } else {
        for (int i = 0; i < num; i++) {        
            _activeMultimouses[i] = new va::Mouse();
            
            // establish mouse pointers as touches
            for(unsigned int j=0; j<_eventHandlers.size(); ++j) {
            	_eventHandlers[j]->rawTouchEnter(i, 10, 10, 10.0f );
            }            
        }    
    }
}

Mice::~Mice() {
    ManyMouse_Quit();
    
    for( std::map<int,va::Mouse*>::const_iterator iter = _activeMultimouses.begin();
       iter != _activeMultimouses.end();
       ++iter )
    {
        va::Mouse* mmouse = iter->second;
        
        // de-establish mouse pointers as touches
        for(unsigned int j=0; j<_eventHandlers.size(); ++j) {
            _eventHandlers[j]->rawTouchLeave( iter->first, 
                                              mmouse->getX(), 
                                              mmouse->getY(), 
                                              10.0f );
        }
        
        // delete mouse
        delete mmouse;          
    }    
    
    _activeMultimouses.clear();
}


void Mice::update() {
    ManyMouseEvent event;
    while (ManyMouse_PollEvent(&event)) {
        if (event.type == MANYMOUSE_EVENT_RELMOTION) {
        	//This is what we get under OSX
            if (_activeMultimouses.find(event.device) != _activeMultimouses.end()) {
                va::Mouse* mmouse = _activeMultimouses[event.device];
                if (event.item == 0) {
                    //dx
                    mmouse->setX( osg::clampBetween((int)(mmouse->getX()+0.8*event.value),
                                 0, (int)_width) );
                } else {
                    //dy
                    mmouse->setY( osg::clampBetween((int)(mmouse->getY()-0.8*event.value),
                                 0, (int)_height) );                
                }
                
                for(unsigned int j=0; j<_eventHandlers.size(); ++j) {
                    _eventHandlers[j]->rawTouchMove( event.device, 
                                                     mmouse->getX(), 
                                                     mmouse->getY(), 
                                                     10.0f );
                }                  
                
                
            }
        } else if (event.type == MANYMOUSE_EVENT_ABSMOTION) {
            //This is what we get under Windows
            if (_activeMultimouses.find(event.device) != _activeMultimouses.end()) {
                va::Mouse* mmouse = _activeMultimouses[event.device];
                if (event.item == 0) {
                    //dx
                    mmouse->setX( (event.value*_width)/65536 );
                    //osg::constrain
                } else {
                    //dy
                    mmouse->setY( _height-(event.value*_height)/65536 );
                }

                for(unsigned int j=0; j<_eventHandlers.size(); ++j) {
                    _eventHandlers[j]->rawTouchMove( event.device, 
                                                     mmouse->getX(), 
                                                     mmouse->getY(), 
                                                     10.0f );
                }                  
                
            }
        } else if (event.type == MANYMOUSE_EVENT_BUTTON) {
            if (_activeMultimouses.find(event.device) != _activeMultimouses.end()) {
            	va::Mouse* mmouse = _activeMultimouses[event.device];
                mmouse->setButton(event.item);
                if (event.value) {
                    //down
                    //_activeMultimouseShapes[event.device]->fillMode();
                    for(unsigned int j=0; j<_eventHandlers.size(); ++j) {
                        _eventHandlers[j]->rawTouchDown( event.device, 
                                                         mmouse->getX(), 
                                                         mmouse->getY(), 
                                                         10.0f);
                    }                      
                } else {
                    //up
                    //_activeMultimouseShapes[event.device]->lineMode();
                    for(unsigned int j=0; j<_eventHandlers.size(); ++j) {
                        _eventHandlers[j]->rawTouchUp( event.device, 
                                                       mmouse->getX(), 
                                                       mmouse->getY(), 
                                                       10.0f);
                    }                      
                }
			}
        } else if (event.type == MANYMOUSE_EVENT_DISCONNECT) {
            if (_activeMultimouses.find(event.device) != _activeMultimouses.end()) {
                va::Mouse* mmouse = _activeMultimouses[event.device];
                
                // de-establish mouse as touche
                for(unsigned int j=0; j<_eventHandlers.size(); ++j) {
                	osg::notify(osg::NOTICE) << "leave: " << event.device << std::endl;
                    _eventHandlers[j]->rawTouchLeave( event.device, 
                                                      mmouse->getX(), 
                                                      mmouse->getY(), 
                                                      10.0f );
                }
                
                _activeMultimouses.erase(event.device);
            }
        }
    }
}


void Mice::addEventHandler( va::RawTouchHandler* handler ) {
    _eventHandlers.push_back(handler);
    
    //if we have mice, also sent rawTouchEnter events to handler
    for( std::map<int,va::Mouse*>::const_iterator iter = _activeMultimouses.begin();
       iter != _activeMultimouses.end();
       ++iter )
    {
        va::Mouse* mmouse = iter->second;
        handler->rawTouchEnter(iter->first, mmouse->getX(), mmouse->getY(), 10.0f );
    }    
}



//std:vector<std::string> Scene::getMultimouseDeviceNames() {
//	std::vector<std::string> mice;
//    for (int i = 0; i < _numManyMouse; i++) {
//    	mice.push_back(ManyMouse_DeviceName(i));
//    }
//    return mice;
//}
