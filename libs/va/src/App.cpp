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

#include <va/App.h>
#include <va/Scene.h>

using namespace va;


App::App() {
    scene = new Scene();

    scene->addUpdateHandler(this);
    scene->addResizeHandler(this);
    scene->addKeyHandler(this);
    scene->addTouchHandler(this);
    scene->addMouseHandler(this);
    scene->addPenHandler(this);

    //osg::setNotifyLevel(osg::WARN);
}

int App::run() {
    return scene->run();
}


