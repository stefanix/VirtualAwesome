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
* TextShape is a node that renders a block of text.
* It is important to note that this class has to nifty
* function to assign text to it: setText(...) and appendText(...)
* They both know how to implicitly convert various types to a
* string. You directly pass it a float for example.
* In fact you can pass it anything you could also pass to a
* ostreamstring.
*
*/

#ifndef VA_TEXTSHAPE
#define VA_TEXTSHAPE

#include <string>
#include <sstream>
#include <osgText/Text>
#include <va/Shape.h>

namespace va {


class TextShape : public Shape {
    public:
    
        enum  Layout { LEFT_TO_RIGHT, RIGHT_TO_LEFT, VERTICAL };
  
        TextShape();
        TextShape( float w, float h );
        void reshape( float w, float h );        
        void reshape();
        
        void setWidth( float w );
        float getWidth() { return _width; }
        void setHeight( float h );        
        float getHeight() { return _height; }
        void setPadding( float padding );
        float getPadding();
        void setPaddingLeft( float padding );
        void setPaddingRight( float padding );
        void setPaddingTop( float padding );
        void setPaddingBottom( float padding );
        float getPaddingLeft() {return _paddingLeft;}
        float getPaddingRight() {return _paddingRight;}
        float getPaddingTop() {return _paddingTop;}
        float getPaddingBottom() {return _paddingBottom;}
        void setLayout( Layout layout );
        void setCharacterSize( float size );
        float getCharacterSize();             
        
        std::string getText();
        // To add text, numbers, etc
        // use appendText(...) and setText(...)
        // to assign text to this class. both of them take
        // strings, floats, ints, ...            
        // Eg: appendText("Number is: ").appendText(42)
        template <class T>
        TextShape& appendText(const T& x) {
            _ss.str("");
            _ss << getText() << x;
            _text->setText(_ss.str());
            return *this;
        }                
        template <class T>
        TextShape& setText(const T& x) {
            _ss.str("");
            _ss << x;
            _text->setText(_ss.str());
            return *this;
        }   
        
        void setColor( float r, float g, float b, float a );
        void setColor( const osg::Vec4& color );
        const osg::Vec4&  getColor();
                   
        // OSG stuff
        osg::ref_ptr<osgText::Text> getOsgText() {return _text;}
                                                            
            
    protected:
        osg::ref_ptr<osgText::Text> _text;
        std::string _defaultTypeface;  
        float _width, _height;
        std::ostringstream _ss;
        
        float _characterSize;
        float _paddingLeft, _paddingRight, _paddingTop, _paddingBottom;
    
        void init( float w, float h );
};


}
#endif