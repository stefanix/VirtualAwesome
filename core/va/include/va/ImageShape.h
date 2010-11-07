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

#ifndef VA_IMAGESHAPE
#define VA_IMAGESHAPE

#include <osgDB/ReadFile>
#include <osg/Image>
#include <osg/Texture2D>
#include <va/Shape.h>
#include <va/TextureGeometry.h>

namespace va {


class ImageShape : public Shape {
    public:
    
        ImageShape();
        ImageShape( const std::string& filename );
        ImageShape( osg::Image* image );
        ImageShape( float w, float h );
        ImageShape( float w, float h, const std::string& filename );
        ImageShape( float w, float h, osg::Image* image );
        void reshape( float w, float h );
        void reshape();
                
        void setWidth( float w );
        float getWidth() {return _width;}
        void setHeight( float h );
        float getHeight() {return _height;}
            
        void loadImage( const std::string& filename );        
        void setImage( osg::Image* image ); 
        
        void setColor( float r, float g, float b, float a );
        void setColor( const osg::Vec4& color );
        const osg::Vec4& getColor();                      
                

    protected:
        float _width;
        float _height;
        osg::ref_ptr<osg::Image>      _image;
        osg::ref_ptr<TextureGeometry> _texture;
        
        void init();
};


}
#endif