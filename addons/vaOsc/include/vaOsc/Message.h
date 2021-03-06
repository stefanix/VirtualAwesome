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

#ifndef VAOSC_MESSAGE
#define VAOSC_MESSAGE

#include <vector>
#include <string>
#include <vaOsc/Arg.h>

namespace vaOsc {


class Message {
  public:
  
	Message() {}
	~Message();
	Message( const Message& other ) {copyFrom(other);}
	Message& operator= ( const Message& other ) {return copyFrom(other);}
	Message& copyFrom( const Message& other );

	std::string getAddress() const {return address;}
	std::string getRemoteIp() {return remote_host;}
	int getRemotePort() {return remote_port;}

	int getNumArgs() const;
	ArgType getArgType( int index ) const;
	std::string getArgTypeName( int index ) const;

    /// get argument by index
    /// use getArgType(index) first to assure using correct function
    /// (eg for an int argument, getArgType(index)==OF_TYPE_INT
	/// or getArgTypeName(index)=="int")
    long getArgAsInt( int index ) const;
	float getArgAsFloat( int index ) const;
	std::string getArgAsString( int index ) const;

	/// message construction
	void setAddress( std::string _address ) {address = _address;};
	void setRemoteEndpoint( std::string host, int port ) {remote_host = host; remote_port = port;}
	void addIntArg( long argument );
	void addFloatArg( float argument );
	void addStringArg( std::string argument );


  protected:

	std::string address;
	std::vector<Arg*> args;

	std::string remote_host;
	int remote_port;
};


}
#endif

