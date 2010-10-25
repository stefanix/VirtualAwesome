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

#ifndef VANETWORK_AWESOMESOCKET
#define VANETWORK_AWESOMESOCKET

#include <map>
#include <vector>
#include <osg/Notify>
#include <va/EventHandlers.h>
#include <vaNetwork/TcpSocket.h>
#include <vaNetwork/UdpSocket.h>
#include <vaNetwork/TcpListener.h>
#include <vaNetwork/IpAddress.h>
#include <vaNetwork/EventHandlers.h>

namespace vaNetwork {


class AwesomeSocket : public va::UpdateHandler {
  public :

    enum IpProtocol {
        IP_ANY,
        IP_TCP,
        IP_UDP
    };
        
        
    AwesomeSocket();
    ~AwesomeSocket();
        
    // TCP related
    //
    void tcpListen( int port );
    void tcpConnect( std::string ip, int port, float timeout=3.0 );
    void tcpDisconnect( std::string ip, int port );

	// UDP related
    //
    void udpListen( int port );

    // both TCP and UDP
    //
	void setRemoteHost( std::string ip, int port );
    void send( std::string message );
    void send( Packet packet );
    
    void addNetworkHandler( NetworkHandler* handler );    
    void enablePackets() {_usePackets = true;}
    void disablePackets() {_usePackets = false;}
    
    // network polling function, call continously
	void update();        


  protected:
  	
    IpProtocol  _ipProtocol;       // is this a TCP or UDP end point?
    bool _isListener;              // is server (tcp), is receiver (udp)
    bool _usePackets;              // send/receive raw text or packets
            
    UdpSocket*                        _udpSocket;
    TcpListener*                      _tcpListener;
    std::map<std::string,TcpSocket*>  _tcpSocketsByHost;
    
    std::string   _remoteIp;
    int           _remotePort;
    
    Message       _theMessage;    // used to assemble message
    char*         _theBuffer;     // before triggering event handlers
	int           _theBufferSize;
    
    std::vector<NetworkHandler*> _networkHandlers;
    
    std::string getHostString( std::string ip, int port );
        
};


}
#endif

