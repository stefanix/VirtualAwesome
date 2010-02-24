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

#include <va/Model.h>

using namespace va;


Model::Model() {
    _valid = false;
    enableLighting();
    enableAutoNormalization();
}

bool Model::isValid() {
    return _valid;
}

void Model::loadModel( const std::string& filename ) {
    osg::ref_ptr<osg::Node> loadedModel = osgDB::readNodeFile(filename);
    if (loadedModel.valid()) {
        _xform->addChild(loadedModel);
        _valid = true;
    } else {
        _valid = false;
    }   
}