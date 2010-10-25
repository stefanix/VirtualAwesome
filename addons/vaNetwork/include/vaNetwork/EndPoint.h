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

#ifndef VANETWORK_ENDPOINT
#define VANETWORK_ENDPOINT

#include <map>
#include <vector>
#include <OpenThreads/Thread>
#include <osg/Notify>
#include <vaNetwork/TcpSocket.h>
#include <vaNetwork/UdpSocket.h>
#include <vaNetwork/TcpListener.h>
#include <vaNetwork/IpAddress.h>
#include <vaNetwork/EventHandlers.h>

namespace vaNetwork {


class EndPoint : public OpenThreads::Thread {
  public :

    enum IpProtocol {
        IP_ANY,
        IP_TCP,
        IP_UDP
    };
        
        
    EndPoint();
    ~EndPoint();
    
    // TCP related
    //
    void tcpListen( int port, bool usePackets=false );
    void tcpConnect( Host remoteHost );
    void tcpDisconnect( Host remoteHost );

	// UDP related
    //
    void udpListen( int port, bool usePackets=false );

    // both TCP and UDP
    //
    int send( Host remoteHost, std::string );
    int send( Host remoteHost, Packet packet );
    
    void addNetworkHandler( NetworkHandler* handler );
    


  protected:
  	
    IpProtocol  _ipProtocol;       // is this a TCP or UDP end point?
    bool _isListener;              // is server (tcp), is receiver (udp)
    bool _usePackets;              // send/receive raw text or packets
    bool _running;                 // worker thread running
            
    UdpSocket*                        _udpSocket;
    TcpListener*                      _tcpListener;
    std::map<std::string,TcpSocket*>  _tcpSocketsByHost;
    
    Message       _theMessage;    // used to assemble message
    char*         _theBuffer;     // before triggering event handlers
	int           _theBufferSize;
    
    std::vector<NetworkHandler*> _networkHandlers;    
    
	// entry for thread
	void run();    
    
};


}
#endif

