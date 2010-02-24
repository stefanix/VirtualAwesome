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

#include <string>
#include <sstream>
#include <va/TextShape.h>
#include <osg/BoundsChecking>

using namespace va;


TextShape::TextShape() {   
	init(100,100);
}
TextShape::TextShape( float w, float h ) { 
	init(w,h);
}
void TextShape::init( float w, float h ) {        
    _text = new  osgText::Text;
    _geode->addDrawable( _text.get() );
    _defaultTypeface = "TitilliumText400wt.ttf";
    _text->setFont(_defaultTypeface);
    _text->setAlignment(osgText::Text::LEFT_TOP);
    _text->setFontResolution(16,16);
    _characterSize = 16.0f;
     _text->setCharacterSize(_characterSize);
     _paddingLeft = _paddingRight = _paddingTop = _paddingBottom = 0.0f;

    reshape(w,h);
    
    disableLighting();
    disableDepthTest();
    //enableBlending(); 
    
}

void TextShape::reshape( float w, float h) {
    _width = w;    
    _height = h;
    reshape();    
} 
void TextShape::reshape() {    
    _text->setPosition(osg::Vec3(_paddingLeft, _height - _paddingTop, 0.0f));
    _text->setMaximumWidth(_width - _paddingLeft - _paddingRight);
    _text->setMaximumHeight(_height - _paddingTop - _paddingBottom+getCharacterSize());
}
 


void TextShape::setWidth( float w ) {
    _width = w;
    reshape();
}
void TextShape::setHeight( float h ) {
    _height = h;
    reshape();
}
void TextShape::setPadding( float padding ) {
    _paddingLeft = _paddingRight = _paddingTop = _paddingBottom = padding;
    reshape();
}
float TextShape::getPadding(){
	if ( _paddingLeft != _paddingRight || 
         _paddingLeft != _paddingTop || 
         _paddingLeft != _paddingBottom )
    {
        osg::notify(osg::WARN) << "in getPadding, paddings are not equal" << std::endl;
    }
    return _paddingLeft;
}
void TextShape::setPaddingLeft( float padding ){
	_paddingLeft = padding;
    reshape();
}
void TextShape::setPaddingRight( float padding ){
	_paddingRight = padding;
    reshape();
}
void TextShape::setPaddingTop( float padding ){
	_paddingTop = padding;
    reshape();
}
void TextShape::setPaddingBottom( float padding ){
	_paddingBottom = padding;
    reshape();
}

void TextShape::setLayout( Layout layout ) {
    _text->setLayout(osgText::Text::Layout(layout));
}
void TextShape::setCharacterSize( float size ) {
    // many successive calls seem to lead to crashes
    _text->setCharacterSize(size);
}
float TextShape::getCharacterSize() {
    return _text->getCharacterHeight();
}


std::string TextShape::getText() {
    return _text->getText().createUTF8EncodedString();
}


void TextShape::setColor( float r, float g, float b, float a ) {
    _text->setColor(osg::Vec4(r,g,b,a));
}
void TextShape::setColor( const osg::Vec4& color ) {
    _text->setColor(color);
}
const osg::Vec4& TextShape::getColor() {
	return _text->getColor();
}



 
