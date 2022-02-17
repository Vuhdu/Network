#pragma once

#include "NetMessage.h"

class GuaranteeResponse : public NetMessage
{
public:
	GuaranteeResponse();

	void AsServer(sockaddr_in aSocket, int aLength)	override;
	void AsClient(sockaddr_in aSocket, int aLength) override;

private:


};