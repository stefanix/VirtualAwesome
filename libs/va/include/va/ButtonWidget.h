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

#ifndef VA_BUTTONWIDGET
#define VA_BUTTONWIDGET

#include <va/Widget.h>
#include <va/VertexGeometry.h>

namespace va {


class ButtonWidget:  public Widget {
    public:
  
        ButtonWidget();
        ButtonWidget( float w, float h );
        void reshape();
        using Widget::reshape;       
        
        void setLabel( const std::string& name );
        std::string getLabel();
        void setLabelColor( float r, float g, float b, float a ); 
        void setLabelColor( const osg::Vec4& color );
        const osg::Vec4& getLabelColor(); 
                      
        void addEventHandler( ButtonHandler* handler );
        std::vector<ButtonHandler*>&  getEventHandlers();               
        
        void touchDown( Touch& touch );
        void touchMove( Touch& touch );
        void touchUp( Touch& touch );
            
            
    protected:
        osg::ref_ptr<osgText::Text>  _label;  
        std::string _defaultTypeface;  
        std::vector<ButtonHandler*> _handlers;
        osg::Vec4 _buttonPressBorderColor;
        osg::Vec4 _buttonPressBorderColorTemp;
    
        void init( float w, float h );
};


}
#endif