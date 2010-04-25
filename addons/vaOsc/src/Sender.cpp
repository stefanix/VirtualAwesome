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

#include <assert.h>
#include <vaOsc/Sender.h>
#include <oscpack/UdpSocket.h>

using namespace vaOsc;


Sender::Sender( std::string hostname, int port ) {
	socket = new osc::UdpTransmitSocket(osc::IpEndpointName(hostname.c_str(), port));
}

Sender::~Sender() {
    delete socket;
}

void Sender::sendBundle( Bundle& bundle ) {
	static const int OUTPUT_BUFFER_SIZE = 32768;
	char buffer[OUTPUT_BUFFER_SIZE];
	osc::OutboundPacketStream p(buffer, OUTPUT_BUFFER_SIZE );

	// serialize the bundle
	appendBundle( bundle, p );

	socket->Send( p.Data(), p.Size() );
}

void Sender::sendMessage( Message& message ) {
	static const int OUTPUT_BUFFER_SIZE = 16384;
	char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );

	// serialize the message
	p << osc::BeginBundleImmediate;
	appendMessage( message, p );
	p << osc::EndBundle;

	socket->Send( p.Data(), p.Size() );
}

void Sender::appendBundle( Bundle& bundle, osc::OutboundPacketStream& p ) {
	// recursively serialize the bundle
	p << osc::BeginBundleImmediate;
	for ( int i=0; i<bundle.getBundleCount(); i++ ) {
		appendBundle( bundle.getBundleAt( i ), p );
	}
	for ( int i=0; i<bundle.getMessageCount(); i++ ) {
		appendMessage( bundle.getMessageAt( i ), p );
	}
	p << osc::EndBundle;
}

void Sender::appendMessage( Message& message, osc::OutboundPacketStream& p ) {
    p << osc::BeginMessage( message.getAddress().c_str() );
	for ( int i=0; i< message.getNumArgs(); ++i ) {
		if ( message.getArgType(i) == TYPE_INT ) {
			p << message.getArgAsInt( i );
		} else if ( message.getArgType( i ) == TYPE_FLOAT ) {
			p << message.getArgAsFloat( i );
		} else if ( message.getArgType( i ) == TYPE_STRING ) {
			p << message.getArgAsString( i ).c_str();
		} else {
			assert( false && "bad argument type" );
		}
	}
	p << osc::EndMessage;
}
