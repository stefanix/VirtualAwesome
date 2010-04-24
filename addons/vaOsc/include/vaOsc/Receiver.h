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

#ifndef VASOUND_RECEIVER
#define VASOUND_RECEIVER

#include <deque>
#include <OpenThreads/Thread>
#include <oscpack/OscTypes.h>
#include <oscpack/OscPacketListener.h>
#include <oscpack/UdpSocket.h>
#include <vaOsc/Message.h>

namespace vaOsc {


class OscHandler;

class Receiver : public osc::OscPacketListener, public OpenThreads::Thread {
  public:
  
	Receiver( int listen_port );
	~Receiver();

    void addOscHandler( OscHandler* handler );


  protected:

	osc::UdpListeningReceiveSocket* listen_socket;
    std::vector<OscHandler*> _oscHandlers;

	/// process an incoming osc message and add it to the queue
	virtual void ProcessMessage( const osc::ReceivedMessage &m, const osc::IpEndpointName& remoteEndpoint );

	// entry for thread
	void run();
    

};


}
#endif

