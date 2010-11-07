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

#ifndef VA_TOGGLEWIDGET
#define VA_TOGGLEWIDGET

#include <osg/Timer>
#include <va/Widget.h>
#include <va/VertexGeometry.h>

namespace va {

class ToggleWidget;


class ToggleNob : public Widget {
    public:        
    
        ToggleNob( ToggleWidget* toggle );
        void reshape();
        using Widget::reshape;
        
        void setValue( bool checked, bool bNotify=true );
        
        void update();
    
        void touchDown( Touch& touch ){}
        void touchMove( Touch& touch ){}
        void touchUp( Touch& touch ){}
        
    protected:
        friend class ToggleWidget;
        osg::ref_ptr<VertexGeometry> _toggleshape;        
        bool _bToggled;        
        osg::ref_ptr<ToggleWidget> _toggle;
        osg::Timer _flipTimer;
        bool _bAnimate;
        bool _bFlipping;
        float _flipAngle;
        bool _bReached90deg;        
};



class ToggleWidget : public Widget {
    public:
  
        ToggleWidget();
        ToggleWidget( float w, float h );
        void reshape();
        using Widget::reshape;
        
        void setValue( bool checked, bool bNotify=true );        
        bool getValue();

        void setLabel( const std::string& name );
        std::string getLabel();
               
        void setLabelColor( float r, float g, float b, float a ); 
        void setLabelColor( const osg::Vec4& color );
        const osg::Vec4& getLabelColor();
        
        void setNobBackgroundColor( float r, float g, float b, float a ); 
        void setNobBackgroundColor( const osg::Vec4& color );
        const osg::Vec4& getNobBackgroundColor();
        
        void setNobBorderColor( float r, float g, float b, float a ); 
        void setNobBorderColor( const osg::Vec4& color );
        const osg::Vec4& getNobBorderColor(); 
                
                
        void addEventHandler( ToggleHandler* handler );
        std::vector<ToggleHandler*>&  getEventHandlers();
        
        void update(){}
        
        void touchDown( Touch& touch );
        void touchMove( Touch& touch );
        void touchUp( Touch& touch );
            
            
    protected:
        osg::ref_ptr<osgText::Text>  _label;    
        osg::ref_ptr<ToggleNob> _nob;
        std::string _defaultTypeface;  
        std::vector<ToggleHandler*> _handlers;
        osg::Vec4 _buttonPressBorderColor;
        osg::Vec4 _buttonPressBorderColorTemp;
        
        void init( float w, float h );
};


}
#endif