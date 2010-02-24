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

#include <va/TouchShape.h>

using namespace va;


TouchShape::TouchShape() {
    
    _radius = 10.0f;
    enableBlending();
    //make sure this shape appears topmost
    _xform->getOrCreateStateSet()->setRenderBinDetails(60000, "RenderBin");
    
    //circle
    _circleShape = new CircleShape(10);
    _circleShape->setColor(0.6f, 0.0f, 0.0f, 0.5f);
    addChild(_circleShape);

    //circle line
    _circleLineShape = new CircleShape(10);
    _circleLineShape->lineMode();
    _circleLineShape->setColor(0.8f, 0.0f, 0.0f, 1.0f);
    addChild(_circleLineShape);
    //state - line
    //osg::StateSet* stateset = _circleLineShape->getOsgGeode()->getOrCreateStateSet();
    //stateset->setMode(GL_LINE_SMOOTH, osg::StateAttribute::ON);
    //osg::LineWidth* lw = new osg::LineWidth(2.5);
    //stateset->setAttributeAndModes(lw, osg::StateAttribute::ON);  
    
    _circleShape->getOsgXForm()->getOrCreateStateSet()->setRenderBinDetails(2, "RenderBin");
    _circleLineShape->getOsgXForm()->getOrCreateStateSet()->setRenderBinDetails(1, "RenderBin");
    
    
    // text
    _textShape = new TextShape();
    _textShape->getOsgText()->setAlignment(osgText::Text::CENTER_CENTER);
    _textShape->reshape(20,10);
    //_textShape->setFontResolution(16,16);
    //_textShape->setFont(_defaultTypeface);
    _textShape->setCharacterSize(12.0f);
    _textShape->setPosition(osg::Vec3(_radius, _radius, 0.0f)); 
    addChild(_textShape.get());
}

void TouchShape::setText( const std::string& text ) {
    _textShape->setText(text);
}


void TouchShape::setRadius( float r ){
	_radius = r;
	_circleShape->setRadius(r);
	_circleLineShape->setRadius(r);
    _textShape->setPosition(osg::Vec3(r, r, 0.0f));
}

void TouchShape::setDownMode( bool bDown ){
	if (bDown) {
        _circleShape->setColor(0.6f, 0.0f, 0.0f, 0.3f);
    } else {
        _circleShape->setColor(0.6f, 0.0f, 0.0f, 0.1f);
    }

}

