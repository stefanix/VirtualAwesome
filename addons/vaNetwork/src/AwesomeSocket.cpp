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

#include <vaNetwork/AwesomeSocket.h>


namespace vaNetwork {


AwesomeSocket::AwesomeSocket()
	: _ipProtocol(IP_ANY),
      _isListener(false),
      _usePackets(false),
      _udpSocket(NULL),
      _tcpListener(NULL),
      _remoteIp(""),
      _remotePort(0),
      _theBuffer(NULL),
      _theBufferSize(65535)
{
	_theBuffer = new char[_theBufferSize];
}

AwesomeSocket::~AwesomeSocket() {
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

void AwesomeSocket::tcpListen( int port ) {
	if (_ipProtocol == IP_ANY) {
        Socket::Status status;
        _tcpListener = new TcpListener();
        _tcpListener->SetBlocking(true);
        status = _tcpListener->Listen(port);
        _tcpListener->SetBlocking(false);
        
        if (status == vaNetwork::Socket::Done) {
            _ipProtocol = IP_TCP;      // make this a TCP end point
            _isListener = true;        // make this a listener
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

void AwesomeSocket::tcpConnect( std::string ip, int port, float timeout ) {
	if (_ipProtocol == IP_ANY) {
        Socket::Status status;
        TcpSocket* sock = new TcpSocket();
        sock->SetBlocking(true);
        status = sock->Connect(IpAddress(ip), port, timeout);
        if (status == vaNetwork::Socket::Done) {
            _ipProtocol = IP_TCP;  // make this a TCP end point
            sock->SetBlocking(false);
            _tcpSocketsByHost[getHostString(ip,port)] = sock;
            _remoteIp = ip;
            _remotePort = port;             
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

void AwesomeSocket::tcpDisconnect( std::string ip, int port ) {
	if (_ipProtocol == IP_TCP) {        
        std::map<std::string,TcpSocket*>::iterator iter 
                        = _tcpSocketsByHost.find(getHostString(ip,port));
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

void AwesomeSocket::udpListen( int port ) {
	if (_ipProtocol == IP_ANY) {
        Socket::Status status;    	
        
        _udpSocket = new UdpSocket();
        _udpSocket->SetBlocking(true);
        status = _udpSocket->Bind(port);
        _udpSocket->SetBlocking(false);
        
        if (status == vaNetwork::Socket::Done) {
            _ipProtocol = IP_UDP;     // make this a UDP end point
            _isListener = true;       // make this a listener
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

void AwesomeSocket::setRemoteHost( std::string ip, int port ) {
	if (_ipProtocol == IP_ANY) {
        // assume we want to send UDP
        _ipProtocol = IP_UDP;
        _udpSocket = new UdpSocket();
        _udpSocket->SetBlocking(false);
        _remoteIp = ip;
        _remotePort = port;        
    } else if (_ipProtocol == IP_TCP) {
    	// assume we want to change the remote host for TCP
        // only hosts that are already connected are valid
        std::map<std::string,TcpSocket*>::iterator iter 
                        = _tcpSocketsByHost.find(getHostString(ip,port));
        if( iter != _tcpSocketsByHost.end() ) {
        	_remoteIp = ip;
            _remotePort = port;
        } else {
            osg::notify(osg::WARN) << "in setRemoteHost, this host is not connected" << std::endl;
        }
    } else if (_ipProtocol == IP_UDP) {
    	// assume we want to change the remote host for UDP
        _remoteIp = ip;
        _remotePort = port;
    }
}



// both TCP and UDP
//

void AwesomeSocket::send( std::string message ) {
	if (_ipProtocol == IP_TCP) {        
        std::map<std::string,TcpSocket*>::iterator iter 
                        = _tcpSocketsByHost.find(getHostString(_remoteIp,_remotePort));
        if( iter != _tcpSocketsByHost.end() ) {
            iter->second->Send(message.c_str(), message.size() + 1);
        } else {
            osg::notify(osg::WARN) << "in send, this host is not connected" << std::endl;
        }
    } else if (_ipProtocol == IP_UDP) {
    	if(!_udpSocket) { 
            _udpSocket = new UdpSocket();
            _udpSocket->SetBlocking(false);
        }
        _udpSocket->Send(message.c_str(), message.size() + 1, 
        			IpAddress(_remoteIp), _remotePort);
    } else {
        osg::notify(osg::WARN) << "in send, not ready for sending" << std::endl;
    }
}
void AwesomeSocket::send( Packet packet ) {
	if (_ipProtocol == IP_TCP) {        
        std::map<std::string,TcpSocket*>::iterator iter 
                        = _tcpSocketsByHost.find(getHostString(_remoteIp,_remotePort));
        if( iter != _tcpSocketsByHost.end() ) {
            iter->second->Send(packet);
        } else {
            osg::notify(osg::WARN) << "in send, this host is not connected" << std::endl;
        }
    } else if (_ipProtocol == IP_UDP) {
        _udpSocket->Send(packet, IpAddress(_remoteIp), _remotePort);
    } else {
        osg::notify(osg::WARN) << "in send, not ready for sending" << std::endl;
    }
}



void AwesomeSocket::addNetworkHandler( NetworkHandler* handler ){
	_networkHandlers.push_back(handler);
}



void AwesomeSocket::update() {
    if (_ipProtocol == IP_TCP) {
        // accept new connections
        if (_isListener) {
            TcpSocket* sock = new TcpSocket();
            sock->SetBlocking(false);            
            if (_tcpListener->Accept(*sock) == vaNetwork::Socket::Done) {
                // A new client just connected!
                std::string remoteIp = sock->GetRemoteAddress().ToString();
                int remotePort = sock->GetRemotePort();
                _tcpSocketsByHost[getHostString(remoteIp,remotePort)] = sock;
            
                for (unsigned int i=0; i<_networkHandlers.size(); i++) {
                    _networkHandlers[i]->networkConnect(remoteIp,remotePort);
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
            _theMessage._ip = sock->GetRemoteAddress().ToString();
            _theMessage._port = sock->GetRemotePort();
            
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
                    _networkHandlers[i]->networkDisconnect(_theMessage._ip, _theMessage._port);
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
            _theMessage._ip = sender.ToString();
            _theMessage._port = port;
        
            for (unsigned int i=0; i<_networkHandlers.size(); i++) {
                _networkHandlers[i]->networkReceive(_theMessage);
            }
        }
    }
    
}




std::string AwesomeSocket::getHostString( std::string ip, int port ) {
    std::ostringstream ss;
    ss << ip << ":" << port;
    return ss.str();		    
}




}