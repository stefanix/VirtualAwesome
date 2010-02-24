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
* This is the main include file. Include this and you are ready
* to use VirtualAwesome.
*/

#ifndef VA_MAIN
#define VA_MAIN


#include <osgDB/ReadFile>

#include <va/Constants.h>
#include <va/Types.h>
#include <va/Scene.h>

#include <va/Node.h>
#include <va/Model.h>

#include <va/App.h>
#include <va/Shape.h>
#include <va/TriangleShape.h>
#include <va/RectangleShape.h>
#include <va/LineShape.h>
#include <va/EllipseShape.h>
#include <va/CircleShape.h>
#include <va/MonsterShape.h>
#include <va/ImageShape.h>
#include <va/TextShape.h>
#include <va/VertexShape.h>

#include <va/Widget.h>
#include <va/PanelWidget.h>
#include <va/ButtonWidget.h>
#include <va/SliderWidget.h>
#include <va/ToggleWidget.h>


// include the plugins we need
USE_OSGPLUGIN(freetype)


#if defined( TARGET_OSX )
USE_OSGPLUGIN(quicktime)
USE_OSGPLUGIN(bmp)
USE_OSGPLUGIN(osg)
USE_OSGPLUGIN(obj)
USE_OSGPLUGIN(3ds)
USE_OSGPLUGIN(dxf)
USE_OSGPLUGIN(stl)
#elif defined( TARGET_LINUX )
USE_OSGPLUGIN(png)
USE_OSGPLUGIN(jpeg)
USE_OSGPLUGIN(bmp)
USE_OSGPLUGIN(osg)
USE_OSGPLUGIN(obj)
USE_OSGPLUGIN(3ds)
USE_OSGPLUGIN(dxf)
USE_OSGPLUGIN(stl)
#elif defined( TARGET_WIN32 )
USE_OSGPLUGIN(png)
USE_OSGPLUGIN(jpeg)
USE_OSGPLUGIN(bmp)
USE_OSGPLUGIN(osg)
USE_OSGPLUGIN(obj)
USE_OSGPLUGIN(3ds)
USE_OSGPLUGIN(dxf)
USE_OSGPLUGIN(stl)
#endif

// include the platform specific GraphicsWindow implementation.
USE_GRAPHICSWINDOW()

#endif