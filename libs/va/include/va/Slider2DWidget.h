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

#ifndef VA_SLIDER2DWIDGET
#define VA_SLIDER2DWIDGET

#include <osg/BoundsChecking>
#include <va/Widget.h>
#include <va/VertexGeometry.h>

namespace va {


class Slider2DWidget;


class Slider2DNob: public Widget {
    public:      
        
        Slider2DNob( Slider2DWidget* slider );
        void reshape();
        using Widget::reshape;

        void setName( const std::string& name );
        void setValueX( float value, bool bNotify=true );
        void setValueXNormalized( float value, bool bNotify=true );
        void setValueY( float value, bool bNotify=true );
        void setValueYNormalized( float value, bool bNotify=true );
        float getValueX();        
        float getValueY();        

        void touchDown( Touch& touch );
        void touchMove( Touch& touch );
        void touchUp( Touch& touch );


    protected:
        friend class Slider2DWidget; 
        osg::ref_ptr<Slider2DWidget>  _slider;
        std::string  _defaultTypeface;
        osg::ref_ptr<osgText::Text>  _label;
        float _valueX;    //0-1 internally
        float _valueY;    //0-1 internally
        float _valueXMin;
        float _valueXMax;
        float _valueYMin;
        float _valueYMax;
        osg::ref_ptr<VertexGeometry>   _crossLines;
        osg::Vec4 _buttonPressBorderColor;
        osg::Vec4 _buttonPressBorderColorTemp;
        
        void reshapeCrossLinesX( float x );                              
        void reshapeCrossLinesY( float y );                              
};


class Slider2DWidget:  public Widget {
    public:
    
        Slider2DWidget();
        Slider2DWidget( float w, float h );
        void reshape();
        using Widget::reshape;

        void setValueX( float value, bool bNotify=true );
        void setValueXNormalized( float value, bool bNotify=true );
        void setValueY( float value, bool bNotify=true );
        void setValueYNormalized( float value, bool bNotify=true );
        float getValueX();
        float getValueY();
        void setValueXMin( float min );
        void setValueXMax( float max );
        void setValueYMin( float min );
        void setValueYMax( float max );

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
        
        
        void addEventHandler( Slider2DHandler* handler );        
        std::vector<Slider2DHandler*>&  getEventHandlers();        
               

        // Touch Events
        //
        void touchDown( Touch& touch ){}
        void touchMove( Touch& touch ){}
        void touchUp( Touch& touch ){}
              
                
    protected:
    	friend class Slider2DNob;     
        osg::ref_ptr<Slider2DNob>      _nob;
        std::vector<Slider2DHandler*>  _handlers; 
        
        void init( float w, float h );

};


}
#endif