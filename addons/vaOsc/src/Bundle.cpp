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

#include <vaOsc/Bundle.h>

using namespace vaOsc;


Bundle& Bundle::copy( const Bundle& other ) {
	for ( unsigned int i=0; i<other.bundles.size(); i++ ) {
		bundles.push_back( other.bundles[i] );
	}
	for ( unsigned int i=0; i<other.messages.size(); i++ ) {
		messages.push_back( other.messages[i] );
	}
	return *this;
}



void Bundle::addBundle( const Bundle& bundle ) {
	bundles.push_back( bundle );
}

void Bundle::addMessage( const Message& message ) {
	messages.push_back( message );
}
