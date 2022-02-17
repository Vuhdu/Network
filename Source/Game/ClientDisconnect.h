#pragma once

#include "NetMessage.h"

class ClientDisconnect : public NetMessage
{
public:
	ClientDisconnect();

	void AsServer(sockaddr_in aSocket, int aLength) override;
	void AsClient(sockaddr_in aSocket, int aLength) override;
};