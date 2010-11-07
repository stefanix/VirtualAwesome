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

#ifndef VA_PEN
#define VA_PEN

#include <osg/Matrix>

namespace va {

class GuiEvents;


class Pen {
    public:    
        enum TabletPointerType {
            UNKNOWN = 0,
            PEN,
            PUCK,
            ERASER
        };
                
        Pen()
          : _x(0.0f),
            _y(0.0f),
            _pressure(0.0f),
            _tiltX(0.0f),
            _tiltY(0.0f),
            _rotation(0.0f),
            _tabletPointerType(UNKNOWN),
            _time(0.0)
        {}
        
        float getX() { return _x; }
        float getY() { return _y; }

        /// get the pressure, from a tablet input device (range 0 - 1)
        float getPressure()  const { return _pressure; }
        /// get the tiltX, from a tablet input device (range -1 - 1)
        float getTiltX()  const { return _tiltX; }
        /// get the tiltY, from a tablet input device (range -1 - 1)
        float getTiltY()  const { return _tiltY; }
        /// get the rotation, from a tablet input device (range 0 - 2PI)
        float getRotation()  const { return _rotation; }
        /// get the orientation from a tablet input device as a matrix
        const osg::Matrix getOrientation() const {
            float xRad = osg::DegreesToRadians ( getTiltY() );
            float yRad = osg::DegreesToRadians ( getTiltX() );
            float zRad = osg::DegreesToRadians ( getRotation() );
            osg::Matrix xrot = osg::Matrix::rotate ( xRad, osg::Vec3f(1.0f, 0.0f, 0.0f) );
            osg::Matrix yrot = osg::Matrix::rotate ( yRad, osg::Vec3f(0.0f, 0.0f, 1.0f) );
            osg::Matrix zrot = osg::Matrix::rotate ( zRad, osg::Vec3f(0.0f, 1.0f, 0.0f) );
            return ( zrot * yrot * xrot );        
        }
        /// get the current used tablet pointer type
        TabletPointerType getPointerType() const { return _tabletPointerType; }
        double getTime() {return _time;}
        
    protected:
        friend class GuiEvents;
        float _x;
        float _y;    
        float _pressure;
        float _tiltX;
        float _tiltY;
        float _rotation;
        TabletPointerType _tabletPointerType;
        double _time;         
};


}
#endif
