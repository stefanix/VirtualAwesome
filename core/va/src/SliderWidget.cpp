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

#include <va/SliderWidget.h>

using namespace va;


// SliderNob
//

SliderNob::SliderNob( SliderWidget* slider ) {
    _slider = slider;
    _value = 0.5f;
    _valueMin = 0.0f;
    _valueMax = 1.0f;
    _buttonPressBorderColor.set(1.0f, 1.0f, 1.0f, 1.0f);
        
    _label = new  osgText::Text;
    _defaultTypeface = "TitilliumText400wt.ttf";
    _label->setFont(_defaultTypeface);    
    _label->setAlignment(osgText::Text::CENTER_CENTER);
    _label->setFontResolution(32,32);
    _label->setCharacterSize(16.0f);    
    _label->setColor(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
    _geode->addDrawable( _label.get() );

}


void SliderNob::reshape() {
    _background->clearVertices();
    _background->addRoundedRect(0.0f, 0.0f, _width, _height, 6.0f);
    _border->setOsgVertexCount(_background->getOsgVertexCount());
    
    _label->setPosition(osg::Vec3(_width/2.0f, _height/2.0f, 0.0f));
    _label->setMaximumWidth(_width);
    _label->setMaximumHeight(_height);        
}


void SliderNob::setName( const std::string& name ) {
    Widget::setName(name);
    _label->setText(name);    
}


void SliderNob::setValue( float value, bool bNotify ) {
    value = osg::clampBetween(value, _valueMin, _valueMax);
    value = rangemap(value, _valueMin, _valueMax, 0.0f, 1.0f);
    setValueNormalized(value, bNotify);
}
void SliderNob::setValueNormalized( float value, bool bNotify ) {
    if( value != _value ) {
        _value = osg::clampBetween(value, 0.0f, 1.0f);
        float xpos = rangemap(_value, 0.0f, 1.0f, 0.5f*_width, (_slider->getWidth())-0.5f*_width);
        setX(xpos);
        
        if(bNotify) {
            // delegate on-value-change to registered handlers
            for( unsigned int i=0; i<_slider->getEventHandlers().size(); i++) {
                _slider->getEventHandlers()[i]->widget( *_slider );
            }
        }
    }
}
float SliderNob::getValue() {
    return rangemap(_value, 0.0f, 1.0f, _valueMin, _valueMax);
}

void SliderNob::touchDown( Touch& touch ) {
    _buttonPressBorderColorTemp = _border->getColor();
    _border->setColor(_buttonPressBorderColor);  
}
void SliderNob::touchMove( Touch& touch ) {
    if( isDragging(touch) ) {
        float posx = getX();
        posx += getWorldDragDelta(touch)[0];
        posx = osg::clampBetween(posx, 0.5f*_width, (_slider->getWidth())-0.5f*_width);        
        setValueNormalized(rangemap(posx, 0.5f*_width, (_slider->getWidth())-0.5f*_width, 0.0f, 1.0f));
    }
}
void SliderNob::touchUp( Touch& touch ) {
    _border->setColor(_buttonPressBorderColorTemp);
}




// Slider
//

SliderWidget::SliderWidget() {
	init(200,40);
}
SliderWidget::SliderWidget( float w, float h ) {
	init(w,h);
}
void SliderWidget::init( float w, float h ) {

    _background->setColor(0.5f, 0.5f, 0.5f, 0.7f);
               
    // setup slider nob geometry
    _nob = new SliderNob(this);
    addChild(_nob);

    setPosition(0.0f, 0.0f, 0.0f);
    
    _width = w;
    _height = h;
    reshape();    
      
}


void SliderWidget::reshape() {
    _background->clearVertices();
    _background->addRoundedRect(0.0f, 0.5*_height-7.f, _width, 14.f, 7.f);
    _border->setOsgVertexCount(_background->getOsgVertexCount());    
    
    //nob
    _nob->reshape(0.3*_width, 0.8*_height);
    _nob->setPivot(0.5*_nob->getWidth(), 0.5*_nob->getHeight(), 0.f);
    _nob->setPosition(_nob->_value*_width, 0.5*_height, 0.0);
}



void SliderWidget::setValue( float value, bool bNotify ) {
    _nob->setValue(value, bNotify);
}
void SliderWidget::setValueNormalized( float value, bool bNotify ) {
    _nob->setValueNormalized(value, bNotify);
}
float SliderWidget::getValue() {
	return _nob->getValue();
}
void SliderWidget::setValueMin( float min ) {
	_nob->_valueMin = min;
}
void SliderWidget::setValueMax( float max ) {
	_nob->_valueMax = max;
}


void SliderWidget::setLabel( const std::string& name){
    _nob->setName(name); 
}
std::string SliderWidget::getLabel() {
    return _nob->_label->getText().createUTF8EncodedString();
}


void SliderWidget::setLabelColor( float r, float g, float b, float a ) {
    setLabelColor(osg::Vec4(r,g,b,a));
}
void SliderWidget::setLabelColor( const osg::Vec4& color ) {
    _nob->_label->setColor(color);
}
const osg::Vec4& SliderWidget::getLabelColor() {
	return _nob->_label->getColor();
}

void SliderWidget::setNobBackgroundColor( float r, float g, float b, float a ) {
    _nob->_background->setColor(osg::Vec4(r,g,b,a));
}
void SliderWidget::setNobBackgroundColor( const osg::Vec4& color ) {
    _nob->_background->setColor(color);
}
const osg::Vec4& SliderWidget::getNobBackgroundColor() {
	return _nob->_background->getColor();
}

void SliderWidget::setNobBorderColor( float r, float g, float b, float a ) {
    _nob->_border->setColor(osg::Vec4(r,g,b,a));
}
void SliderWidget::setNobBorderColor( const osg::Vec4& color ) {
    _nob->_border->setColor(color);
}
const osg::Vec4& SliderWidget::getNobBorderColor() {
	return _nob->_border->getColor();
}



void SliderWidget::addEventHandler( SliderHandler* handler ){
    _handlers.push_back( handler );
}
std::vector<SliderHandler*>&  SliderWidget::getEventHandlers() {
    return _handlers;
}


