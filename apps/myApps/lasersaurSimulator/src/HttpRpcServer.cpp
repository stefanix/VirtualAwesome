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

#include "HttpRpcServer.h"


namespace vaNetwork {


HttpRpcServer::HttpRpcServer()
	: _tcpListener(NULL),
      _remoteIp(""),
      _remotePort(0),
      _theBuffer(NULL),
      _theBufferSize(65535)
{
	_theBuffer = new char[_theBufferSize];
    _tcpSocketTemp = new TcpSocket();
    _tcpSocketTemp->SetBlocking(false);
}

HttpRpcServer::~HttpRpcServer() {
	delete[] _theBuffer;

	if (_tcpListener) {
        delete _tcpListener;
        _tcpListener = NULL;
    }

    std::map<std::string,TcpSocket*>::iterator iter = _tcpSocketsByHost.begin();
    while (iter != _tcpSocketsByHost.end()) {
    	TcpSocket* sock = iter->second;
        if (sock) {
            delete sock;
            _tcpSocketsByHost.erase(iter++);
        } else {
            ++iter;
        }
    }
    
	if (_tcpSocketTemp) {
        delete _tcpSocketTemp;
        _tcpSocketTemp = NULL;
    }    
}



void HttpRpcServer::listen( int port ) {
	if (_tcpListener) {
        delete _tcpListener;
        _tcpListener = NULL;
    }
    
    Socket::Status status;
    _tcpListener = new TcpListener();
    _tcpListener->SetBlocking(true);
    status = _tcpListener->Listen(port);
    _tcpListener->SetBlocking(false);
    
    if (status != vaNetwork::Socket::Done) {
        // clean up
        delete _tcpListener;
        _tcpListener = NULL;        
        osg::notify(osg::WARN) << "in tcpListen, binding failed" << std::endl;
    }
}

void HttpRpcServer::disconnect( std::string ip, int port ) {
    std::map<std::string,TcpSocket*>::iterator iter 
                    = _tcpSocketsByHost.find(getHostString(ip,port));
    if( iter != _tcpSocketsByHost.end() ) {
        delete iter->second;
        _tcpSocketsByHost.erase(iter);
    }        
}


void HttpRpcServer::setRemoteHost( std::string ip, int port ) {
    // only hosts that are already connected are valid
    std::map<std::string,TcpSocket*>::iterator iter 
                    = _tcpSocketsByHost.find(getHostString(ip,port));
    if( iter != _tcpSocketsByHost.end() ) {
        _remoteIp = ip;
        _remotePort = port;
    } else {
        osg::notify(osg::WARN) << "in setRemoteHost, this host is not connected" << std::endl;
    }
}



void HttpRpcServer::send( std::string message ) {
    std::map<std::string,TcpSocket*>::iterator iter 
                    = _tcpSocketsByHost.find(getHostString(_remoteIp,_remotePort));
    if( iter != _tcpSocketsByHost.end() ) {
        iter->second->Send(message.c_str(), message.size() + 1);
    } else {
        osg::notify(osg::WARN) << "in send, this host is not connected" << std::endl;
    }
}



void HttpRpcServer::addNetworkHandler( NetworkHandler* handler ){
	_networkHandlers.push_back(handler);
}



void HttpRpcServer::update() {
    // accept new connections
    if (_tcpListener->Accept(*_tcpSocketTemp) == vaNetwork::Socket::Done) {
        // A new client just connected!
        std::string remoteIp = _tcpSocketTemp->GetRemoteAddress().ToString();
        int remotePort = _tcpSocketTemp->GetRemotePort();
        _tcpSocketsByHost[getHostString(remoteIp,remotePort)] = _tcpSocketTemp;
        _tcpSocketTemp = new TcpSocket();
        _tcpSocketTemp->SetBlocking(false);
    
        for (unsigned int i=0; i<_networkHandlers.size(); i++) {
            _networkHandlers[i]->networkConnect(remoteIp,remotePort);
        }                  
    }
    
    // receive on all TCP sockets and fire event handlers
    std::map<std::string,TcpSocket*>::iterator iter = _tcpSocketsByHost.begin();
    while (iter != _tcpSocketsByHost.end()) {
        bool iterGotIncremented = false;
        TcpSocket* sock = iter->second;
        Socket::Status status;
        _theMessage.clear();
        _theMessage.setIp(sock->GetRemoteAddress().ToString());
        _theMessage.setPort(sock->GetRemotePort());
        
        std::size_t numCharReceived = 0;
        status = sock->Receive(_theBuffer, _theBufferSize, numCharReceived);
        if (status == vaNetwork::Socket::Done) {
            _theMessage.setText(_theBuffer, numCharReceived);
        }
        
        // notify event handlers
        //
        if (status == vaNetwork::Socket::Done) {
            for (unsigned int i=0; i<_networkHandlers.size(); i++) {
                _networkHandlers[i]->networkReceive(_theMessage);
            }
        } else if (status == vaNetwork::Socket::Disconnected) {
            delete sock;
            _tcpSocketsByHost.erase(iter++);
            iterGotIncremented = true;
            for (unsigned int i=0; i<_networkHandlers.size(); i++) {
                _networkHandlers[i]->networkDisconnect(_theMessage.getIp(), _theMessage.getPort());
            }                    
        }
        
        // increment iter
        // this is done this awkward way because iter might have been
        // invalidated by erase()
        if (!iterGotIncremented) {
            ++iter;
        }
    }
}




std::string HttpRpcServer::getHostString( std::string ip, int port ) {
    std::ostringstream ss;
    ss << ip << ":" << port;
    return ss.str();		    
}



std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    
    std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;    
}


}