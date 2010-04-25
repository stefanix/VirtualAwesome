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

#include <iostream>
#include <assert.h>
#include <osg/Notify>
#include <vaOsc/Message.h>

using namespace vaOsc;


Message::~Message() {
	for ( unsigned int i=0; i<args.size(); ++i ) {
		delete args[i];
    }
	args.clear();
	address = "";
}


int Message::getNumArgs() const {
	return (int)args.size();
}



ArgType Message::getArgType( int index ) const {
    return args.at(index)->getType();
}

std::string Message::getArgTypeName( int index ) const {
    return args.at(index)->getTypeName();
}


long Message::getArgAsInt( int index ) const {
	if ( getArgType(index) == TYPE_INT ) {
    	ArgInt32* argInt32 = dynamic_cast<ArgInt32*>(args.at(index));
    	return static_cast<long>(argInt32->get());
	} else {
        osg::notify(osg::WARN) << "in getArgAsInt(...), not a int" << std::endl;
        return 0;
    }
}

float Message::getArgAsFloat( int index ) const {
	if ( getArgType(index) == TYPE_FLOAT ) {
    	ArgFloat* argFloat = dynamic_cast<ArgFloat*>(args.at(index));
    	return argFloat->get();
	} else {
        osg::notify(osg::WARN) << "in getArgAsFloat(...), not a float" << std::endl;
        return 0.0f;
    }
}

std::string Message::getArgAsString( int index ) const {
	if ( getArgType(index) == TYPE_STRING ) {
    	ArgString* argString = dynamic_cast<ArgString*>(args.at(index));
    	return argString->get();
	} else {
        osg::notify(osg::WARN) << "in getArgAsString(...), not a string" << std::endl;
        return "";
    }
}



void Message::addIntArg( long argument ) {
	args.push_back(new ArgInt32(static_cast<int32_t>(argument)));
}

void Message::addFloatArg( float argument ) {
	args.push_back(new ArgFloat(argument));
}

void Message::addStringArg( std::string argument ) {
	args.push_back(new ArgString(argument));
}






Message& Message::copyFrom( const Message& other ) {
	address = other.address;
	remote_host = other.remote_host;
	remote_port = other.remote_port;

	for ( int i=0; i<(int)other.args.size(); ++i ) {
		ArgType argType = other.getArgType( i );
		if ( argType == TYPE_INT ) {
			args.push_back( new ArgInt32( other.getArgAsInt( i ) ) );
		} else if ( argType == TYPE_FLOAT ) {
			args.push_back( new ArgFloat( other.getArgAsFloat( i ) ) );
		} else if ( argType == TYPE_STRING ) {
			args.push_back( new ArgString( other.getArgAsString( i ) ) );
		} else {
			assert( false && "bad argument type" );
		}
	}

	return *this;
}

