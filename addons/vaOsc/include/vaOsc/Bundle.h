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
* Ported from Damian Stewart's ofxOsc library
* Thanks Damian for open sourcing!
*
* * *
* 
*/

#ifndef VAOSC_BUNDLE
#define VAOSC_BUNDLE

#include <vector>
#include <vaOsc/Message.h>

namespace vaOsc {


class Bundle {
  public:
  	
	Bundle() {}
	~Bundle() {}
	Bundle( const Bundle& other ) {copyFrom(other);}
	Bundle& operator= ( const Bundle& other ) {return copyFrom(other);}
	Bundle& copyFrom( const Bundle& other );
	
	void clear() {messages.clear(); bundles.clear();}

	void addBundle( const Bundle& element );
	void addMessage( const Message& message );
	
	int getBundleCount() const {return bundles.size();}
	int getMessageCount() const {return messages.size();}
	Bundle& getBundleAt( int i ) {return bundles[i];}
	Message& getMessageAt( int i ) {return messages[i];}
	
    
  protected:
  
	std::vector<Message> messages;
	std::vector<Bundle> bundles;
};


}
#endif

