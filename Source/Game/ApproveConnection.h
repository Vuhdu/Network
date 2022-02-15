#pragma once

#include "NetMessage.h"
class ApproveConnection : public NetMessage
{
public:
	ApproveConnection();

	void AsServer(sockaddr_in aSocket, int aLength)	override;
	void AsClient(sockaddr_in aSocket, int aLength) override;

private:

};

