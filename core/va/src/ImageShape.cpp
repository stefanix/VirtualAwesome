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

#include <va/ImageShape.h>

using namespace va;


ImageShape::ImageShape() {
    init();
    reshape(0,0);
}
ImageShape::ImageShape( const std::string& filename ){
    init();
    loadImage(filename);
}
ImageShape::ImageShape( osg::Image* image ){
    init();
    setImage(image);
}
ImageShape::ImageShape( float w, float h ){
    init();
    reshape(w,h);
}
ImageShape::ImageShape( float w, float h, const std::string& filename ){
    init();
    loadImage(filename);
    reshape(w,h);
}
ImageShape::ImageShape( float w, float h, osg::Image* image ){
    init();
    setImage(image);
    reshape(w,h);
}
void ImageShape::init(){
    _texture = new TextureGeometry();
    _texture->setMode(GL_QUADS);
    _geode->addDrawable(_texture->getOsgGeometry().get());    
    
    _texture->addTexCoord(0.0f,1.0f);
    _texture->addTexCoord(0.0f,0.0f);
    _texture->addTexCoord(1.0f,0.0f);
    _texture->addTexCoord(1.0f,1.0f);

    _texture->setNormal(1.0f, 0.0f, 0.0f);
    _texture->setColor(1.0f, 1.0f, 1.0f, 1.0f);

    disableLighting();
    _texture->getOsgTexture()->setResizeNonPowerOfTwoHint(false);
}


void ImageShape::reshape( float w, float h ){
	_width = w;
    _height = h;
    reshape();
}
void ImageShape::reshape(){
	_texture->clearVertices();
    _texture->addVertex(0.f, _height, 0.f);
    _texture->addVertex(0.f, 0.f, 0.f);
    _texture->addVertex(_width, 0.f, 0.f);
    _texture->addVertex(_width, _height, 0.f);
}


void ImageShape::setWidth( float w ) {
    _width = w;
    reshape();
}
void ImageShape::setHeight( float h ) {
    _height = h;
    reshape();
}

    
void ImageShape::loadImage( const std::string& filename ) {
	if(_image.valid()) {_image->unref();}
    _image = osgDB::readImageFile(filename);
    
    if(!_image.valid()) {
    	osg::notify(osg::WARN) << "in Image::loadImage(), failed to load image" << std::endl;
        return;
    }
    
    if(filename.substr(filename.length()-3) == "bmp") {
        _image->flipVertical();
    }    
    
    _texture->setImage(_image);
	reshape(_image->s(), _image->t());
}

void ImageShape::setImage( osg::Image* image ) {
	if(_image.valid()) {_image->unref();}
	_image = image;
    _texture->setImage(_image);
	reshape(_image->s(), _image->t());
}



void ImageShape::setColor( float r, float g, float b, float a ) {
    _texture->setColor(osg::Vec4(r,g,b,a));
}
void ImageShape::setColor( const osg::Vec4& color ) {
    _texture->setColor(color);
}
const osg::Vec4& ImageShape::getColor() {
	return _texture->getColor();
}
