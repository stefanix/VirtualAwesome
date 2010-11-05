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

#ifndef VANETWORK_HTTPRPCSERVER
#define VANETWORK_HTTPRPCSERVER

#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <osg/Notify>
#include <va/EventHandlers.h>
#include <vaNetwork/TcpSocket.h>
#include <vaNetwork/TcpListener.h>
#include <vaNetwork/IpAddress.h>
#include <vaNetwork/EventHandlers.h>

namespace vaNetwork {


class HttpRpcServer : public va::UpdateHandler {
  public:

    HttpRpcServer();
    ~HttpRpcServer();
        
    void listen( int port );
    void disconnect( std::string ip, int port );

	void setRemoteHost( std::string ip, int port );
    void send( std::string message );
    
    void addNetworkHandler( NetworkHandler* handler );    
    
    // network polling function, call continously
	void update();        


  protected:
  	            
    TcpListener*                      _tcpListener;
    std::map<std::string,TcpSocket*>  _tcpSocketsByHost;
    TcpSocket*                        _tcpSocketTemp;
    
    std::string   _remoteIp;
    int           _remotePort;
    
    Message       _theMessage;    // used to assemble message
    char*         _theBuffer;     // before triggering event handlers
	int           _theBufferSize;
    
    std::vector<NetworkHandler*> _networkHandlers;
    
    std::string getHostString( std::string ip, int port );
    std::vector<std::string> split(const std::string &s, char delim);
        
};


}
#endif

