#pragma once

#include "ClientInfo.h"

class ClientManager
{
public:
	static const ClientInfo& AddClient(sockaddr_in anAddress, int aLength);
	static void RemoveClient(const unsigned short aClientID);

	static const ClientInfo const* GetClient(const unsigned short aClientID);
	static const std::vector<ClientInfo>& GetAllClients();

	static bool HasClient(const unsigned short aClientID);


private:
	inline static std::vector<ClientInfo> myClients;

	inline static unsigned short myNextClientID = 0;
};

