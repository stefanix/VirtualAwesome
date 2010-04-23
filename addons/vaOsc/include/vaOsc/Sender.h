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

#ifndef VAOSC_SENDER
#define VAOSC_SENDER

#include <string>
#include <oscpack/OscTypes.h>
#include <oscpack/OscOutboundPacketStream.h>
#include <oscpack/UdpSocket.h>
#include <vaOsc/EventHandlers.h>
#include <vaOsc/Bundle.h>
#include <vaOsc/Message.h>

namespace vaOsc {

class osc::UdpTransmitSocket;


class Sender {
  public:
  
	Sender( std::string hostname, int port );
	~Sender();

	void sendMessage( Message& message );
	void sendBundle( Bundle& bundle );


  private:

	osc::UdpTransmitSocket* socket;
  		
	// helper methods for constructing messages
	void appendBundle( Bundle& bundle, osc::OutboundPacketStream& p );
	void appendMessage( Message& message, osc::OutboundPacketStream& p );

};


}
#endif

