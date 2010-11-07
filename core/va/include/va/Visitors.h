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

#ifndef VA_VISITORS
#define VA_VISITORS

// Visitors
// see: http://www.openscenegraph.org/projects/osg/wiki/Support/Tutorials/FindingNodes

#include <osg/NodeVisitor>
#include <osg/Node>

namespace va {


class zIndexWidgetVisitor : public osg::NodeVisitor {
    // This visitor makes sure zIndex is set in the order
    // of rendering (depth-first traversal) for all widgets
  
    public: 
        zIndexWidgetVisitor();
        void reset( long startZIndex );
        virtual void apply( osg::Geode& geode );

    private:
        long _currentZIndex; 

};


class WidgetFocusVisitor : public osg::NodeVisitor {
    // walks up the graph looking for PanelWidgets
    // brings them to the front
  
    public: 
        WidgetFocusVisitor();
        void reset();
        virtual void apply( osg::PositionAttitudeTransform& group );
        
    protected:
        bool _bKeyboardFocusAssigned;
};



class WidgetTouchEventVisitor : public osg::NodeVisitor {
    // This visitor makes sure widgets respond to touch
    // events according to whether they are visible
  
    public: 
        WidgetTouchEventVisitor();
        void setMode( bool bEnableOrDisable );
        virtual void apply( osg::PositionAttitudeTransform& group );

    private:
        bool _bEnableOrDisable; 

};

}
#endif