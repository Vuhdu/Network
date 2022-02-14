#pragma once


struct ClientInfo
{
	sockaddr_in myAddress;
	int myLength;

	unsigned short myClientID = -1;;

};

