#pragma once

#include "NetMessage.h"

class DestroyObjectMessage : public NetMessage
{
public:
	DestroyObjectMessage();

	void AsServer(sockaddr_in aSocket, int aLength)	override;
	void AsClient(sockaddr_in aSocket, int aLength) override;

	void SetGameObjectID(const int aID);
	int GetGameObjectID() const;

private:
	void RemoveObject();
};