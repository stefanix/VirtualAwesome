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

#include <vaNetwork/EndPoint.h>


namespace vaNetwork {


EndPoint::EndPoint()
	: _ipProtocol(IP_ANY),
      _isListener(false),
      _usePackets(false),
      _udpSocket(NULL),
      _tcpListener(NULL),
      _theBuffer(NULL),
      _theBufferSize(65535)
{
	_theBuffer = new char[_theBufferSize];
}

EndPoint::~EndPoint() {
	delete[] _theBuffer;

	if (_tcpListener) {
        delete _tcpListener;
        _tcpListener = NULL;
    }

	if (_udpSocket) {
        delete _udpSocket;
        _udpSocket = NULL;
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
}




// TCP related
//

void EndPoint::tcpListen( int port, bool usePackets ) {
	if (_ipProtocol == IP_ANY) {
        Socket::Status status;
        _tcpListener = new TcpListener();
        _tcpListener->SetBlocking(false);
        status = _tcpListener->Listen(port);
        
        if (status == vaNetwork::Socket::Done) {
            _ipProtocol = IP_TCP;      // make this a TCP end point
            _isListener = true;        // make this a listener
            _usePackets = usePackets;
        } else {
            // clean up
            delete _tcpListener;
            _tcpListener = NULL;        
            osg::notify(osg::WARN) << "in tcpListen, binding failed" << std::endl;
        }
        
    } else {
        osg::notify(osg::WARN) << "in tcpListen, use only on fresh instance" << std::endl;
    }
}

void EndPoint::tcpConnect( Host remoteHost ) {
	if (_ipProtocol == IP_ANY) {
        Socket::Status status;
        TcpSocket* sock = new TcpSocket();
        sock->SetBlocking(false);
        status = sock->Connect(IpAddress(remoteHost.getAddress()), remoteHost.getPort());
        if (status == vaNetwork::Socket::Done) {
            _ipProtocol = IP_TCP;  // make this a TCP end point
            _tcpSocketsByHost[remoteHost.getHostString()] = sock;
        } else {
            // clean up
            delete sock;
            sock = NULL;
            osg::notify(osg::WARN) << "in tcpConnect, connection failed" << std::endl;
        }
    } else {
        osg::notify(osg::WARN) << "in tcpConnect, use only on fresh instance" << std::endl;
    }
}

void EndPoint::tcpDisconnect( Host remoteHost ) {
	if (_ipProtocol == IP_TCP) {        
        std::map<std::string,TcpSocket*>::iterator iter 
                        = _tcpSocketsByHost.find(remoteHost.getHostString());
        if( iter != _tcpSocketsByHost.end() ) {
            delete iter->second;
            _tcpSocketsByHost.erase(iter);
        }        
        
    } else {
        osg::notify(osg::WARN) << "in tcpDisconnect, use only with TCP" << std::endl;
    }
}




// UDP related
//

void EndPoint::udpListen( int port, bool usePackets ) {
	if (_ipProtocol == IP_ANY) {
        Socket::Status status;    	
        
        _udpSocket = new UdpSocket();
        _udpSocket->SetBlocking(false);
        status = _udpSocket->Bind(port);
        
        if (status == vaNetwork::Socket::Done) {
            _ipProtocol = IP_UDP;     // make this a UDP end point
            _isListener = true;       // make this a listener
            _usePackets = usePackets;
        } else {
            // clean up
            delete _udpSocket;
            _udpSocket = NULL;
            osg::notify(osg::WARN) << "in udpListen, binding failed" << std::endl;
        }

    } else {
        osg::notify(osg::WARN) << "in udpListen, use only on fresh instance" << std::endl;
    }
}




// both TCP and UDP
//

int EndPoint::send( Host remoteHost, std::string ) {

}
int EndPoint::send( Host remoteHost, Packet packet ) {

}



void EndPoint::addNetworkHandler( NetworkHandler* handler ){
	_networkHandlers.push_back(handler);
}



void EndPoint::update() {
    if (_ipProtocol == IP_TCP) {
        // accept new connections
        if (_isListener) {
            TcpSocket* sock = new TcpSocket();
            sock->SetBlocking(false);            
            if (_tcpListener->Accept(*sock) == vaNetwork::Socket::Done) {
                // A new client just connected!            
                _theMessage.clear();
                _theMessage._remoteHost._address = sock->GetRemoteAddress().ToString();
                _theMessage._remoteHost._port = sock->GetRemotePort();
                _tcpSocketsByHost[_theMessage._remoteHost.getHostString()] = sock;
            
                for (unsigned int i=0; i<_networkHandlers.size(); i++) {
                    _networkHandlers[i]->networkConnect(_theMessage._remoteHost);
                }                  
            } else {
                // clean up
                delete sock;
                sock = NULL;
            }
                         
        }
        
        // receive on all TCP sockets and fire event handlers
        std::map<std::string,TcpSocket*>::iterator iter = _tcpSocketsByHost.begin();
        while (iter != _tcpSocketsByHost.end()) {
            bool iterGotIncremented = false;
            TcpSocket* sock = iter->second;
            Socket::Status status;
            _theMessage.clear();
            _theMessage._remoteHost._address = sock->GetRemoteAddress().ToString();
            _theMessage._remoteHost._port = sock->GetRemotePort();
            
            if (_usePackets) {
                status = sock->Receive(_theMessage._packet);
                if (status == vaNetwork::Socket::Done) {
                    _theMessage._usingPackets = true;
                }                
            
            } else {
                std::size_t numCharReceived = 0;
                status = sock->Receive(_theBuffer, _theBufferSize, numCharReceived);
                if (status == vaNetwork::Socket::Done) {
                    _theMessage._text.insert(0, _theBuffer, numCharReceived);
                }
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
                    _networkHandlers[i]->networkDisconnect(_theMessage._remoteHost);
                }                    
            }
            
            // increment iter
            // this is done this awkward way because iter might have been
            // invalidated by erase()
            if (!iterGotIncremented) {
                ++iter;
            }
        }
        
    } else if (_ipProtocol == IP_UDP && _isListener) {
        // receive on all UDP sockets and fire event handlers
        Socket::Status status;
        vaNetwork::IpAddress sender;
        unsigned short port;        
        _theMessage.clear();
        _theMessage._isTcp = false;        
        
        if (_usePackets) {
            status = _udpSocket->Receive(_theMessage._packet, sender, port);
            if (status == vaNetwork::Socket::Done) {
                _theMessage._usingPackets = true;
            }                
        
        } else {
            std::size_t numCharReceived = 0;
            status = _udpSocket->Receive(_theBuffer, _theBufferSize, numCharReceived, sender, port);
            if (status == vaNetwork::Socket::Done) {
                _theMessage._text.insert(0, _theBuffer, numCharReceived);
            }
        }
        
        // notify event handlers
        //
        if (status == vaNetwork::Socket::Done) {
            _theMessage._remoteHost._address = sender.ToString();
            _theMessage._remoteHost._port = port;
        
            for (unsigned int i=0; i<_networkHandlers.size(); i++) {
                _networkHandlers[i]->networkReceive(_theMessage);
            }
        }
    }
    
}






}