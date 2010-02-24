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
* WORK IN PROGRESS
*/

#ifndef VA_BOXSHAPE
#define VA_BOXSHAPE


#include <osg/ShapeDrawable>
#include <va/Shape.h>

namespace va {


class BoxShape : public Shape {

    public:
        
        BoxShape() {
            _shapeGeometry = new osg::ShapeDrawable(new osg::Box( osg::Vec3(0,0,0), 100.f));  
            _geode->addDrawable( _shapeGeometry.get() );      
        }
        
        
        virtual osg::ref_ptr<osg::Drawable>  getOsgDrawable() {
            return _shapeGeometry;
        }
        
    protected:
        osg::ref_ptr<osg::ShapeDrawable> _shapeGeometry;
    
};


}
#endif
