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
* This class is a helper for the Scene class for
* dispatching gui events as they are dispatched by OSG.
* In most cases its functionality would not be used
* directly but through Scene's delegate functions.
*
*/

#ifndef VA_GUIEVENTS
#define VA_GUIEVENTS

#include <vector>
#include <osgViewer/ViewerEventHandlers>
#include <va/EventHandlers.h>
#include <va/Key.h>
#include <va/Mouse.h>
#include <va/Pen.h>

namespace va {


class Scene;


class GuiEvents : public osgGA::GUIEventHandler {
    public:
    
    	GuiEvents();
        void addUpdateHandler( UpdateHandler* handler );      
        void addResizeHandler( ResizeHandler* handler );      
        void addKeyHandler( KeyHandler* handler );
        void addMouseHandler( MouseHandler* handler );
        void addPenHandler( PenHandler* handler );
            
        virtual bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter&);
        virtual void accept(osgGA::GUIEventHandlerVisitor& v)   { v.visit(*this); };


    protected:
        friend class Scene;
        Scene* _scene;
        Key    _keyEvent;
        Mouse  _mouseEvent;
        Pen    _penEvent;
            
        std::vector<UpdateHandler*> _updateHandlers;
        std::vector<ResizeHandler*> _resizeHandlers;            
    	std::vector<KeyHandler*>    _keyHandlers; 
    	std::vector<MouseHandler*>  _mouseHandlers; 
    	std::vector<PenHandler*>    _penHandlers;
};


}
#endif

