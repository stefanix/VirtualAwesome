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


#include <va/TextureGeometry.h>

using namespace va;


TextureGeometry::TextureGeometry(){
    _texcoords = new osg::Vec2Array();
    _geometry->setTexCoordArray(0, _texcoords);
    
    // set up the texture state.
    _texture = new osg::Texture2D();
    _texture->setDataVariance(osg::Object::DYNAMIC);  // protect from being optimized away as static state.
    
    osg::StateSet* stateset = _geometry->getOrCreateStateSet();
    stateset->setTextureAttributeAndModes(0, _texture, osg::StateAttribute::ON);

    _texture->setFilter(osg::Texture2D::MIN_FILTER, osg::Texture2D::LINEAR);
    _texture->setFilter(osg::Texture2D::MAG_FILTER, osg::Texture2D::LINEAR);        
}



// Texture Coordinates
//

void TextureGeometry::addTexCoord( float u, float v ){
    addTexCoord(osg::Vec2(u,v));
}
void TextureGeometry::addTexCoord( const osg::Vec2& texcoord ){
    _texcoords->push_back(texcoord);
    _geometry->dirtyDisplayList();  
}
void TextureGeometry::setTexCoord( unsigned int index, const osg::Vec2& coord ){
	_texcoords->at(index) = coord;
    _geometry->dirtyDisplayList();    
}
const osg::Vec2& TextureGeometry::getTexCoord( unsigned int index ){
    return _texcoords->at(index);
}
void TextureGeometry::clearTexCoords(){
    _texcoords->clear();
    _geometry->dirtyDisplayList();   
}



void TextureGeometry::setImage( osg::Image* image ){
	_texture->setImage(image);
}



// OSG stuff
//

void TextureGeometry::setOsgTexture( osg::Texture2D* texture ){
    _texture->unref();
    _texture = texture; 
}
osg::ref_ptr<osg::Texture2D> TextureGeometry::getOsgTexture(){
    return _texture;
}

void TextureGeometry::setOsgTexCoords(osg::Vec2Array* texcoords){
    _texcoords->unref();
    _texcoords = texcoords;
}
osg::ref_ptr<osg::Vec2Array> TextureGeometry::getOsgTexCoords(){
    return _texcoords;
}

