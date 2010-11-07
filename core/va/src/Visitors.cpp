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

#include <va/Visitors.h>
#include <va/Widget.h>

using namespace va;


zIndexWidgetVisitor::zIndexWidgetVisitor() {
    _currentZIndex = 0;
    setTraversalMode(TRAVERSE_ALL_CHILDREN);
}

void zIndexWidgetVisitor::reset( long startZIndex ) {
    _currentZIndex = startZIndex;
}
        
void zIndexWidgetVisitor::apply( osg::Geode& geode ) {
    Widget* widget = dynamic_cast<Widget*>(geode.getUserData());
    if( widget ) {
        //osg::notify(osg::INFO) << "applying to " << geode.getName() << endl;
        widget->setZIndex(_currentZIndex);
        _currentZIndex++;
    }
}




WidgetFocusVisitor::WidgetFocusVisitor() {
    setTraversalMode(TRAVERSE_PARENTS);
    _bKeyboardFocusAssigned = false;
}

void WidgetFocusVisitor::reset() {
    _bKeyboardFocusAssigned = false;
}

void WidgetFocusVisitor::apply( osg::PositionAttitudeTransform& group ) {
    Widget* widget = dynamic_cast<Widget*>(group.getUserData());
    if( widget ) {
    	if (widget->wantsToFrontOnTouch()) {
            widget->getParent()->bringChildToFront(widget);
        }
    	if (!_bKeyboardFocusAssigned && widget->wantsKeyFocusOnTouch()) {
            FirstKeyHandler::set(widget);
            _bKeyboardFocusAssigned = true;
        }
    }
    traverse(group);
}





WidgetTouchEventVisitor::WidgetTouchEventVisitor() {
    _bEnableOrDisable = true;
    setTraversalMode(TRAVERSE_ALL_CHILDREN);
}

void WidgetTouchEventVisitor::setMode( bool bEnableOrDisable ) {
    _bEnableOrDisable = bEnableOrDisable;
}
        
void WidgetTouchEventVisitor::apply( osg::PositionAttitudeTransform& group ) {
    Widget* widget = dynamic_cast<Widget*>(group.getUserData());
    if( widget ) {
    	if( _bEnableOrDisable ) {
        	// we are traversing to ENABLE
			// only enable if sticky flag is enabled which is in sync
            // when using en/disableTouchEvents() but not when setting
            // it directly as in this visitor; hence it perserves previous state            
            widget->_bTouchEventsEnabled = widget->_bTouchEventsEnabledSticky;
        } else {
        	// we are traversing to DISABLE
            // setting flag directly to perserve sticky flag
            widget->_bTouchEventsEnabled = false;
        }
    }
    traverse(group);
}

