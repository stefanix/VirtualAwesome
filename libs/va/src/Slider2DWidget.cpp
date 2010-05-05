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

#include <va/Slider2DWidget.h>

using namespace va;


// Slider2DNob
//

Slider2DNob::Slider2DNob( Slider2DWidget* slider ) {
    _slider = slider;
    _valueX = 0.5f;
    _valueY = 0.5f;
    _valueXMin = 0.0f;
    _valueXMax = 1.0f;
    _valueYMin = 0.0f;
    _valueYMax = 1.0f;
    _buttonPressBorderColor.set(1.0f, 1.0f, 1.0f, 1.0f);
        
    _label = new  osgText::Text;
    _defaultTypeface = "TitilliumText400wt.ttf";
    _label->setFont(_defaultTypeface);    
    _label->setAlignment(osgText::Text::CENTER_CENTER);
    _label->setFontResolution(32,32);
    _label->setCharacterSize(16.0f);    
    _label->setColor(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
    _geode->addDrawable( _label.get() );
    
    _crossLines = new VertexGeometry();
    _geode->addDrawable(_crossLines->getOsgGeometry().get());
    _crossLines->setMode(GL_LINES);
    _crossLines->setColor(_border->getColor());    
    _crossLines->addVertex(0.0f, 0.0f, 0.0f);
    _crossLines->addVertex(0.0f, 0.0f, 0.0f);
    _crossLines->addVertex(0.0f, 0.0f, 0.0f);
    _crossLines->addVertex(0.0f, 0.0f, 0.0f);
    _crossLines->addVertex(0.0f, 0.0f, 0.0f);
    _crossLines->addVertex(0.0f, 0.0f, 0.0f);
    _crossLines->addVertex(0.0f, 0.0f, 0.0f);
    _crossLines->addVertex(0.0f, 0.0f, 0.0f);    

}


void Slider2DNob::reshape() {
    _background->clearVertices();
    _background->addRoundedRect(0.0f, 0.0f, _width, _height, 6.0f);
    _border->setOsgVertexCount(_background->getOsgVertexCount());
    
    _label->setPosition(osg::Vec3(0.5*_width, 0.5*_height, 0.0f));
    _label->setMaximumWidth(_width);
    _label->setMaximumHeight(_height);
    
    //cross lines
    reshapeCrossLinesX(getX());            
    reshapeCrossLinesY(getY());            
}

void Slider2DNob::reshapeCrossLinesX( float x ) {    
    _crossLines->setVertex(4, osg::Vec3(_width, 0.5*_height, 0.0));  //right
    _crossLines->setVertex(5, osg::Vec3(_slider->_width-x+0.5*_width, 0.5*_height, 0.0));
    _crossLines->setVertex(6, osg::Vec3(0.0, 0.5*_height, 0.0));  //left
    _crossLines->setVertex(7, osg::Vec3(-x+0.5*_width, 0.5*_height, 0.0));    
}
void Slider2DNob::reshapeCrossLinesY( float y ) {
    _crossLines->setVertex(0, osg::Vec3(0.5*_width, _height, 0.0));  //top
    _crossLines->setVertex(1, osg::Vec3(0.5*_width, _slider->_height-y+0.5*_height, 0.0));
    _crossLines->setVertex(2, osg::Vec3(0.5*_width, 0.0, 0.0));  //bottom
    _crossLines->setVertex(3, osg::Vec3(0.5*_width, -y+0.5*_height, 0.0));    
}


void Slider2DNob::setName( const std::string& name ) {
    Widget::setName(name);
    _label->setText(name);    
}


void Slider2DNob::setValueX( float value, bool bNotify ) {
    value = osg::clampBetween(value, _valueXMin, _valueXMax);
    value = rangemap(value, _valueXMin, _valueXMax, 0.0f, 1.0f);
    setValueXNormalized(value, bNotify);
}
void Slider2DNob::setValueXNormalized( float value, bool bNotify ) {
    if( value != _valueX ) {
        _valueX = osg::clampBetween(value, 0.0f, 1.0f);
        float xpos = rangemap(_valueX, 0.0f, 1.0f, 0.5f*_width, _slider->getWidth()-0.5f*_width);
        setX(xpos);
        reshapeCrossLinesX(xpos);        
        
        if(bNotify) {
            // delegate on-value-change to registered handlers
            for( unsigned int i=0; i<_slider->getEventHandlers().size(); i++) {
                _slider->getEventHandlers()[i]->widget( *_slider );
            }
        }
    }
}
void Slider2DNob::setValueY( float value, bool bNotify ) {
    value = osg::clampBetween(value, _valueYMin, _valueYMax);
    value = rangemap(value, _valueYMin, _valueYMax, 0.0f, 1.0f);
    setValueYNormalized(value, bNotify);
}
void Slider2DNob::setValueYNormalized( float value, bool bNotify ) {
    if( value != _valueY ) {
        _valueY = osg::clampBetween(value, 0.0f, 1.0f);
        float ypos = rangemap(_valueY, 0.0f, 1.0f, 0.5f*_height, _slider->getHeight()-0.5f*_height);
        setY(ypos);        
        reshapeCrossLinesY(ypos);
        
        if(bNotify) {
            // delegate on-value-change to registered handlers
            for( unsigned int i=0; i<_slider->getEventHandlers().size(); i++) {
                _slider->getEventHandlers()[i]->widget( *_slider );
            }
        }
    }
}
float Slider2DNob::getValueX() {
    return rangemap(_valueX, 0.0f, 1.0f, _valueXMin, _valueXMax);
}
float Slider2DNob::getValueY() {
    return rangemap(_valueY, 0.0f, 1.0f, _valueYMin, _valueYMax);
}

void Slider2DNob::touchDown( Touch& touch ) {
    _buttonPressBorderColorTemp = _border->getColor();
    _border->setColor(_buttonPressBorderColor);
    _crossLines->setColor(_buttonPressBorderColor);
}
void Slider2DNob::touchMove( Touch& touch ) {
    if( isDragging(touch) ) {
        float posx = getX();
        posx += getWorldDragDelta(touch)[0];
        posx = osg::clampBetween(posx, 0.5f*_width, _slider->getWidth()-0.5f*_width);        
        setValueXNormalized(rangemap(posx, 0.5f*_width, _slider->getWidth()-0.5f*_width, 0.0f, 1.0f));

        float posy = getY();
        posy += getWorldDragDelta(touch)[1];
        posy = osg::clampBetween(posy, 0.5f*_height, _slider->getHeight()-0.5f*_height);        
        setValueYNormalized(rangemap(posy, 0.5f*_height, _slider->getHeight()-0.5f*_height, 0.0f, 1.0f));
    }
}
void Slider2DNob::touchUp( Touch& touch ) {
    _border->setColor(_buttonPressBorderColorTemp);
    _crossLines->setColor(_buttonPressBorderColorTemp);    
}




// Slider
//

Slider2DWidget::Slider2DWidget() {
	init(200,40);
}
Slider2DWidget::Slider2DWidget( float w, float h ) {
	init(w,h);
}
void Slider2DWidget::init( float w, float h ) {

    _background->setColor(0.5f, 0.5f, 0.5f, 0.7f);
               
    // setup slider nob geometry
    _nob = new Slider2DNob(this);
    addChild(_nob);
    
    setPosition(0.0f, 0.0f, 0.0f);
    
    _width = w;
    _height = h;
    reshape();    
      
}


void Slider2DWidget::reshape() {
    _background->clearVertices();
    _background->addRoundedRect(0.0f, 0.0f, _width, _height, 7.f);
    _border->setOsgVertexCount(_background->getOsgVertexCount());    
    
    //nob
    _nob->reshape(0.5*_width, 0.5*_height);
    _nob->setPivot(0.5*_nob->getWidth(), 0.5*_nob->getHeight(), 0.f);
    _nob->setPosition(_nob->_valueX*_width, _nob->_valueY*_height, 0.0);
    _nob->reshapeCrossLinesX(_nob->getX());  
    _nob->reshapeCrossLinesY(_nob->getY());  
}


void Slider2DWidget::setValueX( float value, bool bNotify ) {
    _nob->setValueX(value, bNotify);
}
void Slider2DWidget::setValueXNormalized( float value, bool bNotify ) {
    _nob->setValueXNormalized(value, bNotify);
}
void Slider2DWidget::setValueY( float value, bool bNotify ) {
    _nob->setValueY(value, bNotify);
}
void Slider2DWidget::setValueYNormalized( float value, bool bNotify ) {
    _nob->setValueYNormalized(value, bNotify);
}
float Slider2DWidget::getValueX() {
	return _nob->getValueX();
}
float Slider2DWidget::getValueY() {
	return _nob->getValueY();
}
void Slider2DWidget::setValueXMin( float min ) {
	_nob->_valueXMin = min;
}
void Slider2DWidget::setValueXMax( float max ) {
	_nob->_valueXMax = max;
}
void Slider2DWidget::setValueYMin( float min ) {
	_nob->_valueYMin = min;
}
void Slider2DWidget::setValueYMax( float max ) {
	_nob->_valueYMax = max;
}

void Slider2DWidget::setLabel( const std::string& name){
    _nob->setName(name); 
}
std::string Slider2DWidget::getLabel() {
    return _nob->_label->getText().createUTF8EncodedString();
}


void Slider2DWidget::setLabelColor( float r, float g, float b, float a ) {
    setLabelColor(osg::Vec4(r,g,b,a));
}
void Slider2DWidget::setLabelColor( const osg::Vec4& color ) {
    _nob->_label->setColor(color);
}
const osg::Vec4& Slider2DWidget::getLabelColor() {
	return _nob->_label->getColor();
}

void Slider2DWidget::setNobBackgroundColor( float r, float g, float b, float a ) {
    _nob->_background->setColor(osg::Vec4(r,g,b,a));
}
void Slider2DWidget::setNobBackgroundColor( const osg::Vec4& color ) {
    _nob->_background->setColor(color);
}
const osg::Vec4& Slider2DWidget::getNobBackgroundColor() {
	return _nob->_background->getColor();
}

void Slider2DWidget::setNobBorderColor( float r, float g, float b, float a ) {
    _nob->_border->setColor(osg::Vec4(r,g,b,a));
}
void Slider2DWidget::setNobBorderColor( const osg::Vec4& color ) {
    _nob->_border->setColor(color);
}
const osg::Vec4& Slider2DWidget::getNobBorderColor() {
	return _nob->_border->getColor();
}



void Slider2DWidget::addEventHandler( Slider2DHandler* handler ){
    _handlers.push_back( handler );
}
std::vector<Slider2DHandler*>&  Slider2DWidget::getEventHandlers() {
    return _handlers;
}


