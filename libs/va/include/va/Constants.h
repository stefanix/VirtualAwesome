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

#ifndef VA_CONSTANTS
#define VA_CONSTANTS


#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>

#include <osg/Notify>


//-------------------------------
//  find the system type --------
//-------------------------------

// 		helpful:
// 		http://www.ogre3d.org/docs/api/html/OgrePlatform_8h-source.html

#if defined( __WIN32__ ) || defined( _WIN32 )
	#define TARGET_WIN32
#elif defined( __APPLE_CC__)
	#include <TargetConditionals.h>
    #define TARGET_OSX
#else
	#define TARGET_LINUX
#endif
//-------------------------------



namespace va {


const double PI   = 3.14159265358979323846;
const double PI_2 = 1.57079632679489661923;
const double PI_4 = 0.78539816339744830962;
const double LN_2 = 0.69314718055994530942;
const double INVLN_2 = 1.0 / LN_2;    


//inline std::ostream& always(){
//    return osg::notify(osg::ALWAYS);
//}
//
//inline std::ostream& fatal(){
//    return osg::notify(osg::FATAL);
//}
//
//inline std::ostream& warn(){
//    return osg::notify(osg::WARN);
//}
//
//inline std::ostream& notice(){
//    return osg::notify(osg::NOTICE);
//}
//
//inline std::ostream& info(){
//    return osg::notify(osg::INFO);
//}
//

}
#endif