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

#ifndef VA_TOUCHSHAPE
#define VA_TOUCHSHAPE

#include <va/CircleShape.h>
#include <va/TextShape.h>
#include <va/LineShape.h>

namespace va {


class TouchShape : public Node {
    public:

        TouchShape();        
        void setText( const std::string& text );
        void setRadius( float r );
        void setDownMode( bool bDown );
        
        // Add text, numbers, etc
        // appendText("Number is: ").appendText(42)
        template <class T>
        TouchShape& setText(const T& x) {
            _textShape->setText(x);
            return *this;
        }
        template <class T>
        TouchShape& appendText(const T& x) {
            _textShape->appendText(x);
            return *this;
        }  
                        
    protected:
        float _radius;
        osg::ref_ptr<CircleShape> _circleShape;
        osg::ref_ptr<CircleShape> _circleLineShape;
        osg::ref_ptr<TextShape> _textShape;

};


}
#endif