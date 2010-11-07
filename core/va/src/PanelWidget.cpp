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


#include <va/PanelWidget.h>

using namespace va;


PanelWidget::PanelWidget(){
	init(200,80);
}
PanelWidget::PanelWidget( float w, float h ){
	init(w,h);
}  
void PanelWidget::init( float w, float h ) {
            
    // label
    _label = new  osgText::Text;
    _geode->addDrawable( _label.get() );
    _defaultTypeface = "TitilliumText400wt.ttf";
    _label->setFont(_defaultTypeface);
    _label->setAlignment(osgText::Text::CENTER_CENTER);
	_label->setColor(osg::Vec4(0.5f, 0.5f, 0.5f, 1.f));
    
    setPosition(0.0f, 0.0f, 0.0f);

    _width = w;
    _height = h;
    reshape();
}


void PanelWidget::reshape() {
    // define geometry
    _background->clearVertices();
    _background->setColor(0.0f, 0.0f, 0.0f, 0.4f);
    _background->addRoundedRect(0.0f, 0.0f, _width, _height, 8.f);
    
    //label
    float labelHeight = 20.0f;
    _label->setPosition(osg::Vec3(_width/2.0f, _height-0.5*labelHeight-0.2*labelHeight, 0.0f));
    _label->setCharacterSize(labelHeight);
    _label->setMaximumWidth(_width);
    _label->setMaximumHeight(_height);
}


void PanelWidget::setLabel( const std::string& name){
    _label->setText(name);
}
std::string PanelWidget::getLabel() {
    return _label->getText().createUTF8EncodedString();
}



void PanelWidget::setLabelColor( float r, float g, float b, float a ) {
    setLabelColor(osg::Vec4(r,g,b,a));
}
void PanelWidget::setLabelColor( const osg::Vec4& color ) {
    _label->setColor(color);
}
const osg::Vec4& PanelWidget::getLabelColor() {
	return _label->getColor();
}


// Touch Events
//
void PanelWidget::touchDown( Touch& touch ) {}  
void PanelWidget::touchMove( Touch& touch ) {
    if( isDragging(touch) ) {
        addPosition(getWorldDragDelta(touch));
    }
}
void PanelWidget::touchUp( Touch& touch ) {}

