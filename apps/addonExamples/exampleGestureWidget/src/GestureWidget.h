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
    
