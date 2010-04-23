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
#include <vaOsc/Receiver.h>
#include <OpenThreads/ScopedLock>

using namespace vaOsc;


Receiver::Receiver( int listen_port ) {	
	listen_socket = new osc::UdpListeningReceiveSocket(osc::IpEndpointName(osc::IpEndpointName::ANY_ADDRESS, listen_port), this);

	// start thread, call run() in a new thread
	start();
}


Receiver::~Receiver() {
	if ( listen_socket ) {
		// tell the socket to shutdown
		listen_socket->AsynchronousBreak();
		join();  //waitForThread();
		delete listen_socket;
	}
}


void Receiver::run() {
	// start the socket listener
	listen_socket->Run();
}


void Receiver::ProcessMessage( const osc::ReceivedMessage &m, const osc::IpEndpointName& remoteEndpoint ) {
	// convert the m to a Message
	Message* message = new Message();

	// set the address
	message->setAddress( m.AddressPattern() );

	// set the sender ip/host
	char endpoint_host[ osc::IpEndpointName::ADDRESS_STRING_LENGTH ];
	remoteEndpoint.AddressAsString( endpoint_host );
    message->setRemoteEndpoint( endpoint_host, remoteEndpoint.port );

	// transfer the arguments
	for ( osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
		  arg != m.ArgumentsEnd();
		  ++arg )
	{
		if ( arg->IsInt32() ) {
			message->addIntArg( arg->AsInt32Unchecked() );
		} else if ( arg->IsFloat() ) {
			message->addFloatArg( arg->AsFloatUnchecked() );
		} else if ( arg->IsString() ) {
			message->addStringArg( arg->AsStringUnchecked() );
		} else {
			assert( false && "message argument is not int, float, or string" );
		}
	}

	// now add to the queue
	// at this point we are running inside the thread created by startThread,
	// so anyone who calls hasWaitingMessages() or getNextMessage() is coming
	// from a different thread
	// so we have to practise shared memory management
    
	OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_mutex);
	messages.push_back( message );
}


bool Receiver::hasWaitingMessages() {
	OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_mutex);
	return messages.size() > 0;
}


Message Receiver::getNextMessage() {
	OpenThreads::ScopedLock<OpenThreads::Mutex> lock(_mutex);
	Message message;
	if ( messages.size() > 0 ) {
        Message* src_message = messages.front();
        message.copy( *src_message );
        delete src_message;
        messages.pop_front();
    }
	return message;
}


