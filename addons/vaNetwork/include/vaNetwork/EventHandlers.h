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



class Message {
  public:
    
	Message() { clear(); }
    
    void clear() {
        _isTcp = true;
    	_usingPackets = false;
        _text = "";
        _packet.Clear();
        _ip = "";
        _port = 0;
    }

    bool usingPackets() {return _usingPackets;}
    
    void setText(char* chars, int numChars) {_text.insert(0, chars, numChars);}
	std::string getText() {return _text;}
	Packet getPacket() {return _packet;}   // to use call AwesomeSocket::enablePackets()

	void setIp( std::string ip ) {_ip = ip;}
	std::string getIp() {return _ip;}
    
	void setPort( int port ) {_port = port;}    
	int getPort() {return _port;}

    bool isTcpMessage() {return _isTcp;}
    bool isUdpMessage() {return !_isTcp;}
    

  protected:
	friend class AwesomeSocket;

    bool _isTcp;                   // is this a TCP or UDP message    
	bool _usingPackets;            // using raw text or packets
	std::string _text;
    Packet _packet;
    
	std::string _ip;
	int         _port;
	
};



class NetworkHandler {
    public:
        virtual ~NetworkHandler() {}
        
        virtual void networkConnect( std::string ip, int port ) {}
        virtual void networkDisconnect( std::string ip, int port ) {}
        virtual void networkReceive( Message message ) {}
};


}
#endif

