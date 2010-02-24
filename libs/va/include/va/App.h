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

#ifndef VA_APP
#define VA_APP

#include <osg/ref_ptr>
#include <osg/Referenced>
#include <va/Constants.h>
#include <va/EventHandlers.h>

namespace va {


class Scene;


class App : public osg::Referenced,
			public UpdateHandler, 
            public ResizeHandler,
            public KeyHandler, 
            public TouchHandler, 
            public MouseHandler, 
            public PenHandler,
            public ButtonHandler, 
            public SliderHandler, 
            public ToggleHandler {
            
    public:

        osg::ref_ptr<Scene>  scene;
  
        App();
        virtual ~App(){}
        virtual int run();        
        
        virtual void update(){}
        virtual void resize( int w, int h ){}

        virtual void keyPress( Key& key ){}
        virtual void keyRelease( Key& key ){}

        virtual void touchEnter( Touch& touch ){}
        virtual void touchDown( Touch& touch ){}
        virtual void touchMove( Touch& touch ){}
        virtual void touchUp( Touch& touch ){}
        virtual void touchLeave( Touch& touch ){}
        
        virtual void mouseButton( Mouse& mouse ){}
        virtual void mouseScroll( Mouse& mouse ){}

        virtual void penPressure( Pen& pen ){}
        virtual void penOrientation( Pen& pen ){}
        virtual void penEnter( Pen& pen ){}
        virtual void penLeave( Pen& pen ){}

        virtual void widgetButton( ButtonWidget& button ){}
        virtual void widgetSlider( SliderWidget& slider ){}
        virtual void widgetToggle( ToggleWidget& toggle ){}
            
};


}
#endif

