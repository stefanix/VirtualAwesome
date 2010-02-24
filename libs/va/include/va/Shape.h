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

#ifndef VA_SHAPE
#define VA_SHAPE

#include <va/Node.h>

namespace va {


class Shape : public Node {
    public:
        virtual ~Shape(){}
        
        virtual void reshape(){}
        
        virtual void lineMode(){}
        virtual void fillMode(){}       
};



}
#endif
