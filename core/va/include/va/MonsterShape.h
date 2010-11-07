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

#ifndef VA_MONSTERSHAPE
#define VA_MONSTERSHAPE

#include <va/Shape.h>
#include <va/VertexGeometry.h>
#include <va/VertexShape.h>

namespace va {


class MonsterShape: public Shape {

    public:

        MonsterShape();        
        
        void setColor( float r, float g, float b, float a );
        void setColor( const osg::Vec4& color );
    
    protected:
        osg::ref_ptr<VertexShape> _body;
        osg::ref_ptr<VertexShape> _mouth;
        osg::ref_ptr<VertexShape> _leye;
        osg::ref_ptr<VertexShape> _reye;
        
    
};


}
#endif