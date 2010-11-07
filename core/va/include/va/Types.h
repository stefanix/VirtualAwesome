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

#ifndef VA_TYPES
#define VA_TYPES

namespace va {


class Drawable: public osg::Referenced {
    public:
        virtual osg::ref_ptr<osg::Drawable>  getOsgDrawable() = 0;
};


}
#endif

