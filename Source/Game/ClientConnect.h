#pragma once

#include "NetMessage.h"

class ClientConnect : public NetMessage
{
public:
	ClientConnect();

	void AsServer(sockaddr_in aSocket, int aLength) override;
	void AsClient(sockaddr_in aSocket, int aLength) override;

private:


};

class Ping : public NetMessage
{
public:
	Ping();

	void AsServer(sockaddr_in aSocket, int aLength) override;
	void AsClient(sockaddr_in aSocket, int aLength) override;

private:


};