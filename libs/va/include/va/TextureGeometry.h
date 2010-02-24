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

#ifndef VA_TEXTUREGEOMETRY
#define VA_TEXTUREGEOMETRY

#include <osg/Texture2D>
#include <va/VertexGeometry.h>

namespace va {


class TextureGeometry : public VertexGeometry {

    public:

        TextureGeometry();
                
        void addTexCoord( float u, float v );
        void addTexCoord( const osg::Vec2& texcoord );  
        void setTexCoord( unsigned int index, const osg::Vec2& coord );
        const osg::Vec2& getTexCoord( unsigned int index );
        void clearTexCoords();        
        
        void setImage( osg::Image* image );

        
        // OSG stuff
        void setOsgTexture( osg::Texture2D* texture );
        osg::ref_ptr<osg::Texture2D> getOsgTexture();
        void setOsgTexCoords(osg::Vec2Array* texcoords);
        osg::ref_ptr<osg::Vec2Array> getOsgTexCoords();
        
    
    protected:
      
        osg::ref_ptr<osg::Texture2D> _texture;
        osg::ref_ptr<osg::Vec2Array> _texcoords;
    
};


}
#endif
