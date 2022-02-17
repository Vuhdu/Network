#pragma once

#include "NetMessage.h"

class InstantiateMessage : public NetMessage
{
public:
	InstantiateMessage();

	void AsServer(sockaddr_in aSocket, int aLength)	override;
	void AsClient(sockaddr_in aSocket, int aLength) override;

	void SetGameObjectID(const int aID);

private:



};