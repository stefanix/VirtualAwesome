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
#include <vaOsc/Message.h>

using namespace vaOsc;


Message::~Message() {
	clear();
}

void Message::clear() {
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
    if ( index >= (int)args.size() ) {
        fprintf(stderr,"Message::getArgType: index %d out of bounds\n", index );
        return OSC_TYPE_INDEXOUTOFBOUNDS;
    } else {
        return args[index]->getType();
    }
}

std::string Message::getArgTypeName( int index ) const {
    if ( index >= (int)args.size() ) {
        fprintf(stderr,"Message::getArgTypeName: index %d out of bounds\n", index );
        return "INDEX OUT OF BOUNDS";
    } else {
        return args[index]->getTypeName();
    }
}


int32_t Message::getArgAsInt32( int index ) const {
	if ( getArgType(index) != OSC_TYPE_INT32 ) {
	    if ( getArgType( index ) == OSC_TYPE_FLOAT ) {
            fprintf(stderr, "Message:getArgAsInt32: warning: converting int32 to float for argument %i\n", index );
            return ((ArgFloat*)args[index])->get();
        } else {
            fprintf(stderr, "Message:getArgAsInt32: error: argument %i is not a number\n", index );
            return 0;
        }
	} else {
        return ((ArgInt32*)args[index])->get();
    }
}


float Message::getArgAsFloat( int index ) const {
	if ( getArgType(index) != OSC_TYPE_FLOAT ) {
	    if ( getArgType( index ) == OSC_TYPE_INT32 ) {
            fprintf(stderr, "Message:getArgAsFloat: warning: converting float to int32 for argument %i\n", index );
            return ((ArgInt32*)args[index])->get();
        } else {
            fprintf(stderr, "Message:getArgAsFloat: error: argument %i is not a number\n", index );
            return 0;
        }
	} else {
        return ((ArgFloat*)args[index])->get();
    }
}


std::string Message::getArgAsString( int index ) const {
    if ( getArgType(index) != OSC_TYPE_STRING ) {
	    if ( getArgType( index ) == OSC_TYPE_FLOAT ) {
            char buf[1024];
            sprintf(buf,"%f",((ArgFloat*)args[index])->get() );
            fprintf(stderr, "Message:getArgAsString: warning: converting float to string for argument %i\n", index );
            return buf;
        } else if ( getArgType( index ) == OSC_TYPE_INT32 ) {
            char buf[1024];
            sprintf(buf,"%i",((ArgInt32*)args[index])->get() );
            fprintf(stderr, "Message:getArgAsString: warning: converting int32 to string for argument %i\n", index );
            return buf;
        } else {
            fprintf(stderr, "Message:getArgAsString: error: argument %i is not a string\n", index );
            return "";
        }
	} else {
        return ((ArgString*)args[index])->get();
    }
}





void Message::addIntArg( int32_t argument ) {
	args.push_back( new ArgInt32( argument ) );
}

void Message::addFloatArg( float argument ) {
	args.push_back( new ArgFloat( argument ) );
}

void Message::addStringArg( std::string argument ) {
	args.push_back( new ArgString( argument ) );
}






Message& Message::copy( const Message& other ) {
	// copy address
	address = other.address;

	remote_host = other.remote_host;
	remote_port = other.remote_port;

	// copy arguments
	for ( int i=0; i<(int)other.args.size(); ++i ) {
		ArgType argType = other.getArgType( i );
		if ( argType == OSC_TYPE_INT32 ) {
			args.push_back( new ArgInt32( other.getArgAsInt32( i ) ) );
		} else if ( argType == OSC_TYPE_FLOAT ) {
			args.push_back( new ArgFloat( other.getArgAsFloat( i ) ) );
		} else if ( argType == OSC_TYPE_STRING ) {
			args.push_back( new ArgString( other.getArgAsString( i ) ) );
		} else {
			assert( false && "bad argument type" );
		}
	}

	return *this;
}

