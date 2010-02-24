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

#ifndef VA_SLIDERWIDGET
#define VA_SLIDERWIDGET

#include <osg/BoundsChecking>
#include <va/Widget.h>
#include <va/VertexGeometry.h>

namespace va {


class SliderWidget;


class SliderNob: public Widget {
    public:      
        
        SliderNob( SliderWidget* slider );
        void reshape();
        using Widget::reshape;

        void setName( const std::string& name );
        void setValue( float value, bool bNotify=true );
        void setValueNormalized( float value, bool bNotify=true );
        float getValue();        

        void touchDown( Touch& touch );
        void touchMove( Touch& touch );
        void touchUp( Touch& touch );


    protected:
    	friend class SliderWidget; 
        osg::ref_ptr<SliderWidget>  _slider;
        std::string  _defaultTypeface;
        osg::ref_ptr<osgText::Text>  _label;
        float _value;    //0-1 internally
        float _valueMin;
        float _valueMax;
        osg::Vec4 _buttonPressBorderColor;
        osg::Vec4 _buttonPressBorderColorTemp;             
};


class SliderWidget:  public Widget {
    public:
    
        SliderWidget();
        SliderWidget( float w, float h );
        void reshape();
        using Widget::reshape;

        void setValue( float value, bool bNotify=true );
        void setValueNormalized( float value, bool bNotify=true );
        float getValue();
        void setValueMin( float min );
        void setValueMax( float max );

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
        
        
        void addEventHandler( SliderHandler* handler );        
        std::vector<SliderHandler*>&  getEventHandlers();        
               

        // Touch Events
        //
        void touchDown( Touch& touch ){}
        void touchMove( Touch& touch ){}
        void touchUp( Touch& touch ){}
              
                
    protected:           
        osg::ref_ptr<SliderNob>      _nob;
        std::vector<SliderHandler*>  _handlers;     
        
        void init( float w, float h );
};


}
#endif