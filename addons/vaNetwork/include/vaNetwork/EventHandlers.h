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

#ifndef VANETWORK_EVENTHANDLERS
#define VANETWORK_EVENTHANDLERS

#include <string>
#include <sstream>
#include <vaNetwork/Packet.h>

namespace vaNetwork {



class Host {
  public:
    

	Host()
    	: _address(""),
          _port(0)
    {}
    
	Host( std::string address, int port )
    	: _address(address),
          _port(port)
    {}
    
    std::string getAddress() {return _address;}
    int getPort() {return _port;}
    std::string getHostString() {
        std::ostringstream ss;
        ss << _address << ":" << _port;
        return ss.str();		    
    }
    
    
  protected:
	friend class EndPoint;
    friend class Message;
    
	std::string _address;
    int         _port;
    
};



class Message {
  public:
    
	Message() { clear(); }
    
    void clear() {
        _isTcp = true;
    	_usingPackets = false;
        _text = "";
        _packet.Clear();
        _remoteHost._address = "";
        _remoteHost._port = 0;
    }

    bool usingPackets() {return _usingPackets;}
	std::string getText() {return _text;}
	Packet getPacket() {return _packet;}   // to use call EndPoint::enablePackets()

	Host getHost() {return _remoteHost;}
	std::string getRemoteAddress() {return _remoteHost.getAddress();}
	int getRemotePort() {return _remoteHost.getPort();}

    bool isTcpMessage() {return _isTcp;}
    bool isUdpMessage() {return !_isTcp;}
    

  protected:
	friend class EndPoint;

    bool _isTcp;                   // is this a TCP or UDP message    
	bool _usingPackets;            // using raw text or packets
	std::string _text;
    Packet _packet;
    
	Host _remoteHost;
	
};



class NetworkHandler {
    public:
        virtual ~NetworkHandler() {}
        
        // NOTE: these handlers are typically called from a different thread.
        // networkConnect/networkDisconnect are only relevant for TCP
        //
        virtual void networkConnect( Host host ) {}
        virtual void networkDisconnect( Host hosts ) {}
        virtual void networkReceive( Message message ) {}
};


}
#endif

