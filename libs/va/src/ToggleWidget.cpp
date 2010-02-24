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


#include <va/ToggleWidget.h>
#include <va/Shape.h>

using namespace va;


// ToggleNob
//

ToggleNob::ToggleNob( ToggleWidget* toggle ) {
    _bToggled = false;
    _toggle = toggle;
    _bFlipping = false;
    _flipAngle = 0.0f;
    _bReached90deg = false;
    _bAnimate = true;
    _width = _height= 100;
    
    _toggleshape = new VertexGeometry();
    _toggleshape->setMode(GL_LINES);
    _toggleshape->setColor(0.5f, 0.5f, 0.5f, 1.0f);
    _geode->addDrawable( _toggleshape->getOsgGeometry() );
    _toggleshape->setVisible(false);
    osg::StateSet* stateset = _toggleshape->getOsgGeometry()->getOrCreateStateSet();
    stateset->setMode(GL_LINE_SMOOTH, osg::StateAttribute::ON);
    osg::LineWidth* lw = new osg::LineWidth(4.0);
    stateset->setAttributeAndModes(lw, osg::StateAttribute::ON);
    
    // make touch events "bubble up" to Toggle
    disableTouchEvents();
}


void ToggleNob::reshape() {
    _background->clearVertices();
    _background->addRoundedRect(0.0f, 0.0f, _width, _height, 6.0f);
	_border->setOsgVertexCount(_background->getOsgVertexCount());
    
    //check shape
    _toggleshape->clearVertices();
    _toggleshape->addVertex(0.25*_width, 0.25*_height, 0.0f);
    _toggleshape->addVertex(0.75*_width, 0.75*_height, 0.0f);
    _toggleshape->addVertex(0.25*_width, 0.75*_height, 0.0f);
    _toggleshape->addVertex(0.75*_width, 0.25*_height, 0.0f);
}


void ToggleNob::setValue( bool checked, bool bNotify ) {
    if( checked != _bToggled) {
        _bToggled = checked;
        
        if(_bAnimate) {
            _bFlipping = true;
            _flipTimer.setStartTick();
        } else {
            _toggleshape->setVisible(_bToggled);
        }
        
        if (bNotify) {
            // delegate on-change to registered handlers
            for( unsigned int i=0; i<_toggle->getEventHandlers().size(); i++) {
                _toggle->getEventHandlers()[i]->widget( *_toggle );
            }
        }
    }
}

void ToggleNob::update() {
    if( _bFlipping ) {
        _flipAngle = 8*_flipTimer.time_s();
        if( _flipAngle >= osg::PI/1.8f && !_bReached90deg ) {
            _bReached90deg = true;
            //half of ratation => show/hide check shape
            if(_toggle->getValue()) {
                _toggleshape->setVisible(true);
            } else {
                _toggleshape->setVisible(false);
            }
        } else if (_flipAngle >= osg::PI) {
            //end of rotation
            _flipAngle = 0;
            _bFlipping = false;
            _bReached90deg = false;       
        }
        setRotation( _flipAngle, 0.0f, 1.0f, 0.0f );
    }
}




// Toggle
//

ToggleWidget::ToggleWidget() {
	init(100,40);
}
ToggleWidget::ToggleWidget( float w, float h ) {
	init(w,h);
}
void ToggleWidget::init( float w, float h ) {
    
    _background->setColor(0.0f, 0.0f, 0.0f, 0.2f);
    
    // label
    _label = new osgText::Text;
    _defaultTypeface = "TitilliumText400wt.ttf";
    _label->setAlignment(osgText::Text::LEFT_CENTER);
    _label->setColor(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
    _label->setFont(_defaultTypeface);
    _geode->addDrawable( _label.get() );
    
    // setup slider nob geometry
    _nob = new ToggleNob(this);
    addChild(_nob);
    
    setPosition(0.0f, 0.0f, 0.0f);    
    _buttonPressBorderColor.set(1.0f, 1.0f, 1.0f, 1.0f);

    _width = w;
    _height = h;
    reshape();
}


void ToggleWidget::reshape() {
    // define geometry
    _background->clearVertices();
    _background->addRoundedRect(0.0f, 0.0f, _width, _height, 6.0f);
    
    //label
    _label->setPosition(osg::Vec3(1.4*_height, _height/2.0f, 0.0f));
    _label->setCharacterSize(_height/2.5f);
    _label->setMaximumWidth(_width - 1.4*_height);
    _label->setMaximumHeight(_height);
    
    //nob
    _nob->reshape(_height, _height);
    _nob->setPivot(0.5*_nob->getWidth(), 0.5*_nob->getHeight(), 0.f);
    _nob->setPosition(0.5*_nob->getWidth(), 0.5*_nob->getHeight(), 0.0);    
}




void ToggleWidget::setValue( bool checked, bool bNotify ) {
    _nob->setValue(checked, bNotify);
}

bool ToggleWidget::getValue() {
    return _nob->_bToggled;
}


void ToggleWidget::setLabel( const std::string& name){
    _label->setText(name);
}
std::string ToggleWidget::getLabel() {
    return _label->getText().createUTF8EncodedString();
}


void ToggleWidget::setLabelColor( float r, float g, float b, float a ) {
    setLabelColor(osg::Vec4(r,g,b,a));
}
void ToggleWidget::setLabelColor( const osg::Vec4& color ) {
    _label->setColor(color);
}
const osg::Vec4& ToggleWidget::getLabelColor() {
	return _label->getColor();
}


void ToggleWidget::setNobBackgroundColor( float r, float g, float b, float a ) {
    _nob->_background->setColor(osg::Vec4(r,g,b,a));
}
void ToggleWidget::setNobBackgroundColor( const osg::Vec4& color ) {
    _nob->_background->setColor(color);
}
const osg::Vec4& ToggleWidget::getNobBackgroundColor() {
	return _nob->_background->getColor();
}

void ToggleWidget::setNobBorderColor( float r, float g, float b, float a ) {
    _nob->_border->setColor(osg::Vec4(r,g,b,a));
}
void ToggleWidget::setNobBorderColor( const osg::Vec4& color ) {
    _nob->_border->setColor(color);
}
const osg::Vec4& ToggleWidget::getNobBorderColor() {
	return _nob->_border->getColor();
}


void ToggleWidget::addEventHandler( ToggleHandler* handler ){
    _handlers.push_back( handler );
}
std::vector<ToggleHandler*>&  ToggleWidget::getEventHandlers() {
    return _handlers;
}


// Events
//
void ToggleWidget::touchDown( Touch& touch ) {
    _buttonPressBorderColorTemp = _nob->_border->getColor();
    _nob->_border->setColor(_buttonPressBorderColor);    
}  
void ToggleWidget::touchMove( Touch& touch ) {
    //std::cout << "touchMove on: " << getName() << std::endl;
}
void ToggleWidget::touchUp( Touch& touch ) {
    _nob->_border->setColor(_buttonPressBorderColorTemp);
    
    // only trigger if still inside widget
    const osg::Vec3& touchpos = touch.getPosition();
    if( touchpos[0] > 0 && touchpos[0] < _width && touchpos[1] > 0 && touchpos[1] < _height ) {
        setValue( !_nob->_bToggled );
    }
}
    
