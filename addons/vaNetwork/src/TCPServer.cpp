/*
* Copyright 2009 OpenFrameworks <http://openframeworks.cc>
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

#include <vaNetwork/TCPServer.h>
#include <vaNetwork/TCPClient.h>

using namespace vaNetwork;


//--------------------------
TCPServer::TCPServer(){
	verbose		= true;
	connected	= false;
	count		= 0;
	port		= 0;
	str			= "";
    _running    = false;

	TCPConnections = new TCPClient[TCP_MAX_CLIENTS];
}

//--------------------------
TCPServer::~TCPServer(){
	close();
}

//--------------------------
void TCPServer::setVerbose(bool _verbose){
	verbose = _verbose;
}

//--------------------------
bool TCPServer::setup(int _port, bool blocking){
	if( !_TCPServer.Create() ){
		if(verbose)printf("TCPServer: create() failed\n");
		return false;
	}
	if( !_TCPServer.Bind(_port) ){
		if(verbose)printf("TCPServer: bind(port = %i) failed\n", _port);
		return false;
	}

	connected		= true;
	port			= _port;
	bClientBlocking = blocking;

    _running = true;
	start();
    
	return true;
}

//--------------------------
bool TCPServer::close(){

	if(!connected) return true;

	for(int i = 0; i < count; i++){
		TCPConnections[i].close();
	}
    
    _running = false;

	cancel(); //stop the thread, cancel might be too brutal?

	if( !_TCPServer.Close() ){
		if(verbose)printf("TCPServer: unable to close connection\n");
		return false;
	}else{
		connected = false;
		return true;
	}
}

//--------------------------
bool TCPServer::disconnectClient(int clientID){
	if( !isClientSetup(clientID) ){
		if(verbose)printf("TCPServer: client %i doesn't exist\n", clientID);
		return false;
	}
	else if(TCPConnections[clientID].close()){
		return true;
	}
	return false;
}

//--------------------------
bool TCPServer::send(int clientID, std::string message){
	if( !isClientSetup(clientID) ){
		if(verbose)printf("TCPServer: client %i doesn't exist\n", clientID);
		return false;
	}
	else{
		TCPConnections[clientID].send(message);
		return true;
	}
}

//--------------------------
bool TCPServer::sendToAll(std::string message){
	if(count == 0) return false;

	for(int i = 0; i < count; i++){
		if(TCPConnections[i].isConnected())TCPConnections[i].send(message);
	}
	return true;
}

//--------------------------
std::string TCPServer::receive(int clientID){
	if( !isClientSetup(clientID) ){
		if(verbose)printf("TCPServer: client %i doesn't exist\n", clientID);
		return "client doesn't exist";
	}

	return TCPConnections[clientID].receive();
}

//--------------------------
bool TCPServer::sendRawBytes(int clientID, const char * rawBytes, const int numBytes){
	if( !isClientSetup(clientID) ){
		if(verbose)printf("TCPServer: client %i doesn't exist\n", clientID);
		return false;
	}
	else{
		return TCPConnections[clientID].sendRawBytes(rawBytes, numBytes);
	}
}

//--------------------------
bool TCPServer::sendRawBytesToAll(const char * rawBytes, const int numBytes){
	if(count == 0 || numBytes <= 0) return false;

	for(int i = 0; i < count; i++){
		if(TCPConnections[i].isConnected())TCPConnections[i].sendRawBytes(rawBytes, numBytes);
	}
	return true;
}

//--------------------------
int TCPServer::getNumReceivedBytes(int clientID){
	if( !isClientSetup(clientID) ){
		if(verbose)printf("TCPServer: client %i doesn't exist\n", clientID);
		return 0;
	}

	return TCPConnections[clientID].getNumReceivedBytes();
}

//--------------------------
int TCPServer::receiveRawBytes(int clientID, char * receiveBytes,  int numBytes){
	if( !isClientSetup(clientID) ){
		if(verbose)printf("TCPServer: client %i doesn't exist\n", clientID);
		return 0;
	}

	return TCPConnections[clientID].receiveRawBytes(receiveBytes, numBytes);
}

//--------------------------
int TCPServer::getClientPort(int clientID){
	if( !isClientSetup(clientID) ){
		if(verbose)printf("TCPServer: client %i doesn't exist\n", clientID);
		return 0;
	}
	else return TCPConnections[clientID].getPort();
}

//--------------------------
std::string TCPServer::getClientIP(int clientID){
	if( !isClientSetup(clientID) ){
		if(verbose)printf("TCPServer: client %i doesn't exist\n", clientID);
		return "000.000.000.000";
	}
	else return TCPConnections[clientID].getIP();
}

//--------------------------
int TCPServer::getNumClients(){
	return count;
}

//--------------------------
int TCPServer::getPort(){
	return port;
}

//--------------------------
bool TCPServer::isConnected(){
	return connected;
}

//--------------------------
bool TCPServer::isClientSetup(int clientID){
	return (clientID < count && clientID < TCP_MAX_CLIENTS);
}

//--------------------------
bool TCPServer::isClientConnected(int clientID){
	return isClientSetup(clientID) && TCPConnections[clientID].isConnected();
}

//don't call this
//--------------------------
void TCPServer::run(){

	while( _running ){

		if(count == TCP_MAX_CLIENTS){
			if(verbose)printf("TCPServer: reached max connected clients! \nTCPServer: no more connections accepted\n");
			break;
		}

		if( !_TCPServer.Listen(TCP_MAX_CLIENTS) ){
			if(verbose)printf("TCPServer: Listen() failed\n");
		}

		if( !_TCPServer.Accept(TCPConnections[count]._TCPClient) ){
			if(verbose)printf("TCPServer: Accept() failed\n");
			continue;
		}else{
			TCPConnections[count].setup(count, bClientBlocking);
			count++;
			if(verbose)printf("TCPServer: client %i connected on port %i\n", count, TCPConnections[count].getPort());
		}
	}
	if(verbose)printf("TCPServer: listen thread ended\n");
}





