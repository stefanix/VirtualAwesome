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

#ifndef VA_MODELSHAPE
#define VA_MODELSHAPE


#include <osg/Light>
#include <osg/LightSource>
#include <osgDB/ReadFile>
#include <va/Node.h>

namespace va {


class Model: public Node {
    public:
    
        Model();
                
        bool isValid();
        void loadModel( const std::string& filename );
    

    protected:
        bool _valid;
};


class Light: public Node {
    public:
    
        Light() {
            _light = new osg::Light;
            _light->setLightNum(1);
            _light->setAmbient(osg::Vec4(0.2f,0.2f,0.2f,1.0f));
            _light->setDiffuse(osg::Vec4(0.1f,0.4f,0.1f,1.0f));
            _light->setConstantAttenuation(1.0f);
            
            _lightSource = new osg::LightSource();
            _lightSource->setLight(_light.get());
            
            osg::StateSet* stateset = _xform->getOrCreateStateSet();
            stateset->setMode(GL_LIGHTING, osg::StateAttribute::ON);

            _lightSource->setLocalStateSetModes(osg::StateAttribute::ON);
            _lightSource->setStateSetModes(*stateset,osg::StateAttribute::ON);

            _xform->addChild(_lightSource.get());        
        }
                        

    protected:
        osg::ref_ptr<osg::LightSource> _lightSource;
        osg::ref_ptr<osg::Light> _light;
};


}
#endif