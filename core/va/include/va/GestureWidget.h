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
* The GestureWidget is a Widget that can recognize basic
* multitouch gestures: Two finger drag, pinch-zoom, two finger rotate
* These gestures are then applied in expected ways to the transform
* of the widget.
*
* Internally the GestureWidget uses two transforms. The usual _xform
* and the optional _xform2. Any Node can have this _xform2 enabled and
* it allows for more complex transformations. In this case this is very
* very handy because it makes sure the gesture transforms do not interfer
* with the manual widget transforms in unexpected ways.
*/

#ifndef VA_GESTUREWIDGET
#define VA_GESTUREWIDGET

#include <va/Widget.h>
#include <va/VertexGeometry.h>


namespace va {


class GestureWidget : public Widget {
    
    public:
    
        GestureWidget();
        GestureWidget( float w, float h );
        void reshape();
        using Widget::reshape;
        
        // enablers/disablers
        // of basic gestures
        //
        void enableDragging() {_bDraggingEnabled = true;}
        void disableDragging() {_bDraggingEnabled = false;}
        void enableTwoTouchMove() {_bTwoTouchMoveEnabled = true;}
        void disableTwoTouchMove() {_bTwoTouchMoveEnabled = false;}
        void enableTwoTouchScale() {_bTwoTouchScaleEnabled = true;}
        void disableTwoTouchScale() {_bTwoTouchScaleEnabled = false;}
        void enableTwoTouchRotate() {_bTwoTouchRotateEnabled = true;}
        void disableTwoTouchRotate() {_bTwoTouchRotateEnabled = false;}

        void touchDown( va::Touch& touch );
        void touchMove( va::Touch& touch );
        void touchUp( va::Touch& touch );
        
        
	protected:
        
        bool _bDraggingEnabled;  // single touch
        bool _bTwoTouchMoveEnabled;
        bool _bTwoTouchScaleEnabled;
        bool _bTwoTouchRotateEnabled;
        
        osg::Quat touchDownQuat;
        float touchDownScale;
        
        void init( float w, float h );
        
};

}
#endif
    
