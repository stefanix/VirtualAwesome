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

#include <va/Constants.h>
#include <cstdlib>
#include <ctime>

using namespace va;



std::ostream& va::always(){
    return osg::notify(osg::ALWAYS);
}

std::ostream& va::fatal(){
    return osg::notify(osg::FATAL);
}

std::ostream& va::warn(){
    return osg::notify(osg::WARN);
}

std::ostream& va::notice(){
    return osg::notify(osg::NOTICE);
}

std::ostream& va::info(){
    return osg::notify(osg::INFO);
}



void va::seedRandom(){
	seedRandom(time(NULL));
}

void va::seedRandom( long seed ){
	std::srand(seed);
}

float va::random(float min, float max){
	return min + ((max-min) * std::rand()/(RAND_MAX + 1.0));
}


float va::rangemap(float r1val, float r1min, float r1max, float r2min, float r2max) {
    /**
    *                     r1val
    *    |- - - - -|--------x----|
    *    0       r1min       \  r1max
    *                         \
    *    |- - - - - -|---------x-------|
    *    0         r2min      return  r2max
    */
    return (r1val - r1min) * ((r2max - r2min)/(r1max - r1min)) + r2min;
}
