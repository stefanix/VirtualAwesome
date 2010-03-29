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

#ifndef VANETWORK_TCPSERVER
#define VANETWORK_TCPSERVER

#include <string>
#include <OpenThreads/Thread>
#include <vaNetwork/TCPManager.h>

namespace vaNetwork {


#define TCP_MAX_CLIENTS  32

//forward decleration
class TCPClient;

class TCPServer : public OpenThreads::Thread {

	public:

		TCPServer();
		~TCPServer();
		void setVerbose(bool _verbose);
		bool setup(int _port, bool blocking = false);
		bool close();
		bool disconnectClient(int clientID);

		int getNumClients();
		int getPort();
		bool isConnected();

		int getClientPort(int clientID);
		std::string getClientIP(int clientID);

		bool isClientSetup(int clientID);
		bool isClientConnected(int clientID);

		//send data as a string - a short message
		//is added to the end of the string which is
		//used to indicate the end of the message to
		//the receiver see: STR_END_MSG (TCPClient.h)
		bool send(int clientID, std::string message);
		bool sendToAll(std::string message);

		//send and receive raw bytes lets you send and receive
		//byte (char) arrays without modifiying or appending the data.
		//Strings terminate on null bytes so this is the better option
		//if you are trying to send something other than just ascii strings

		bool sendRawBytes(int clientID, const char * rawBytes, const int numBytes);
		bool sendRawBytesToAll(const char * rawBytes, const int numBytes);

		//the received message length in bytes
		int getNumReceivedBytes(int clientID);

		//get the message as a string
		//this will only work with messages coming via
		//send() and sendToAll()
		//or from messages terminating with the STR_END_MSG
		//which by default is  [/TCP]
		//eg: if you want to send "Hello World" from other
		//software and want to receive it as a string
		//sender should send "Hello World[/TCP]"
		std::string receive(int clientID);

		//pass in buffer to be filled - make sure the buffer
		//is at least as big as numBytes
		int receiveRawBytes(int clientID, char * receiveBytes,  int numBytes);


		//don't call this
		//--------------------------
		void run();


		TCPManager  _TCPServer;
		TCPClient*  TCPConnections;


	protected:

		bool         connected, verbose;
		std::string  str;
		int          count, port;
		bool         bClientBlocking;
        
        bool         _running;
};


}
#endif



