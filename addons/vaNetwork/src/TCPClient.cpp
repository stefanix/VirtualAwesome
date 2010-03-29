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

#include <vaNetwork/TCPClient.h>

using namespace vaNetwork;


//--------------------------
TCPClient::TCPClient(){

	verbose		= false;
	connected	= false;
	messageSize = 0;
	port		= 0;
	index		= -1;
	str			= "";
	tmpStr		= "";
	ipAddr		="000.000.000.000";

	partialPrevMsg = "";

	memset(tmpBuff,  0, TCP_MAX_MSG_SIZE+1);
}

//--------------------------
TCPClient::~TCPClient(){
	close();
}

//--------------------------
void TCPClient::setVerbose(bool _verbose){
	verbose = _verbose;
}

//--------------------------
bool TCPClient::setup(std::string ip, int _port, bool blocking){

	if( !_TCPClient.Create() ){
		if(verbose)printf("TCPClient: Create() failed\n");
		return false;
	}else if( !_TCPClient.Connect((char *)ip.c_str(), _port) ){
		if(verbose)printf("TCPClient: Connect(%s, %i) failed\n", ip.c_str(), _port);
		_TCPClient.Close(); //we free the connection
		return false;
	}

	_TCPClient.SetNonBlocking(!blocking);

	port		= _port;
	ipAddr		= ip;
	connected	= true;
	return true;
}

//don't use this one
//for server to use internally only!
//--------------------------
bool TCPClient::setup(int _index, bool blocking){
	index = _index;

	//this fetches the port that the server
	//sets up the connection on
	//different to the server's listening port
	InetAddr addr;
	if( _TCPClient.GetRemoteAddr(&addr) ){
		port   =  addr.GetPort();
		ipAddr =  addr.DottedDecimal();
	}

	_TCPClient.SetNonBlocking(!blocking);
	connected 	= true;
	return true;
}


//--------------------------
bool TCPClient::close(){
	if( connected ){

		if( !_TCPClient.Close() ){
			if(verbose)printf("TCPClient: Close() failed\n");
			return false;
		}else{
			connected = false;
			return true;
		}
	}else{
		return true;
	}
}

//--------------------------
bool TCPClient::send(std::string message){
	// tcp is a stream oriented protocol
	// so there's no way to be sure were
	// a message ends without using a terminator
	// note that you will receive a trailing [/TCP]\0
	// if sending from here and receiving from receiveRaw or
	// other applications
	message = partialPrevMsg + message + STR_END_MSG;
	message += (char)0; //for flash
	int ret = _TCPClient.SendAll( message.c_str(), message.length() );
	if( ret == 0 ){
		if(verbose)printf("TCPClient: other side disconnected\n");
		close();
		return false;
	}else if(ret<0){
		if(verbose)printf("TCPClient: sendAll() failed\n");
		return false;
	}else if(ret<(int)message.length()){
		// in case of partial send, store the
		// part that hasn't been sent and send
		// with the next message to not corrupt
		// next messages
		partialPrevMsg=message.substr(ret);
		return true;
	}else{
		partialPrevMsg = "";
		return true;
	}
}

//--------------------------
bool TCPClient::sendRaw(std::string message){
	if( message.length() == 0) return false;

	if( !_TCPClient.SendAll(message.c_str(), message.length()) ){
		if(verbose)printf("TCPClient: sendRawBytes() failed\n");
		close();
		return false;
	}else{
		return true;
	}
}

//--------------------------
bool TCPClient::sendRawBytes(const char* rawBytes, const int numBytes){
	if( numBytes <= 0) return false;

	if( !_TCPClient.SendAll(rawBytes, numBytes) ){
		if(verbose)printf("TCPClient: sendRawBytes() failed\n");
		close();
		return false;
	}else{
		return true;
	}
}


//this only works after you have called receive
//--------------------------
int TCPClient::getNumReceivedBytes(){
	return messageSize;
}

//--------------------------
static void removeZeros(char * buffer, int size){
	for(int i=0;i<size-1;i++){
		if(buffer[i]==(char)0){
			for(int j=i;j<size-1;j++){
				buffer[j]=buffer[j+1];
			}
			buffer[size-1]=(char)0;
		}
	}
}

//--------------------------
std::string TCPClient::receive(){

	str    = "";
	int length=-2;
	//only get data from the buffer if we don't have already some complete message
	if(tmpStr.find(STR_END_MSG)==std::string::npos){
		memset(tmpBuff,  0, TCP_MAX_MSG_SIZE+1); //one more so there's always a \0 at the end for string concat
		length = _TCPClient.Receive(tmpBuff, TCP_MAX_MSG_SIZE);
		if(length>0){ // don't copy the data if there was an error or disconnection
			removeZeros(tmpBuff,length);
			tmpStr += tmpBuff;
		}
	}

	// check for connection reset or disconnection
	if((length==-1 && errno==TCP_CONNRESET ) || length == 0){
		close();
		if(tmpStr.length()==0) // return if there's no more data left in the buffer
			return "";
	}

	// process any available data
	if(tmpStr.find(STR_END_MSG)!=std::string::npos){
		str=tmpStr.substr(0,tmpStr.find(STR_END_MSG));
		tmpStr=tmpStr.substr(tmpStr.find(STR_END_MSG)+STR_END_MSG_LEN);
	}
	return str;
}

//--------------------------
int TCPClient::receiveRawBytes(char * receiveBuffer, int numBytes){
	messageSize = _TCPClient.Receive(receiveBuffer, numBytes);
	if(messageSize==0){
		close();
	}
	return messageSize;
}

//--------------------------
std::string TCPClient::receiveRaw(){
	messageSize = _TCPClient.Receive(tmpBuff, TCP_MAX_MSG_SIZE);
	if(messageSize==0){
		close();
	}
	return tmpBuff;
}

//--------------------------
bool TCPClient::isConnected(){
	return connected;
}

//--------------------------
int TCPClient::getPort(){
	return port;
}

//--------------------------
std::string TCPClient::getIP(){
	return ipAddr;
}






