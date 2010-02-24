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

#include <va/ButtonWidget.h>

using namespace va;


ButtonWidget::ButtonWidget() {
	init(100,40);
}
ButtonWidget::ButtonWidget( float w, float h ) {        
	init(w,h);
}
void ButtonWidget::init( float w, float h ) {
    _label = new  osgText::Text;
    _defaultTypeface = "TitilliumText400wt.ttf";
    _label->setFont(_defaultTypeface);
    _label->setAlignment(osgText::Text::CENTER_CENTER);
    _label->setFontResolution(32,32);
    _label->setCharacterSize(16.0f);
    _label->setColor(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
    _geode->addDrawable( _label.get() );
    
    setPosition(0.0f, 0.0f, 0.0f);    
    _buttonPressBorderColor.set(1.0f, 1.0f, 1.0f, 1.0f);

    _width = w;
    _height = h;
    reshape();
}


void ButtonWidget::reshape() {
    // define geometry
    _background->clearVertices();
    _background->addRoundedRect(0.0f, 0.0f, _width, _height, 0.48*_height);
    _border->setOsgVertexCount(_background->getOsgVertexCount());
    
    //label
    _label->setPosition(osg::Vec3(_width/2.0f, _height/2.0f, 0.0f));
    _label->setMaximumWidth(_width);
    _label->setMaximumHeight(_height);
}


void ButtonWidget::setLabel( const std::string& name){
    _label->setText(name);
}
std::string ButtonWidget::getLabel() {
    return _label->getText().createUTF8EncodedString();
}


void ButtonWidget::setLabelColor( float r, float g, float b, float a ) {
    setLabelColor(osg::Vec4(r,g,b,a));
}
void ButtonWidget::setLabelColor( const osg::Vec4& color ) {
    _label->setColor(color);
}
const osg::Vec4& ButtonWidget::getLabelColor() {
	return _label->getColor();
}


void ButtonWidget::addEventHandler( ButtonHandler* handler ){
    _handlers.push_back( handler );
}
std::vector<ButtonHandler*>&  ButtonWidget::getEventHandlers() {
    return _handlers;
}


// Events
//
void ButtonWidget::touchDown( Touch& touch ) {
    _buttonPressBorderColorTemp = getBorderColor();
    setBorderColor(_buttonPressBorderColor);    
}  
void ButtonWidget::touchMove( Touch& touch ) {
    //std::cout << "touchMove on: " << getName() << std::endl;
}
void ButtonWidget::touchUp( Touch& touch ) {
    setBorderColor(_buttonPressBorderColorTemp); 
    
    // delegate on-touch-up to registered handlers
    // only trigger if still inside widget
    const osg::Vec3& touchpos = touch.getPosition();
    if( touchpos[0] > 0 && touchpos[0] < _width && touchpos[1] > 0 && touchpos[1] < _height ) {
        for( unsigned int i=0; i<_handlers.size(); i++) {
            _handlers[i]->widget( *this );
        }
    }
}
