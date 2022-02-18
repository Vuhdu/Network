#include "stdafx.h"
#include "ClientManager.h"

const ClientInfo& ClientManager::AddClient(sockaddr_in anAddress, int aLength)
{
	ClientInfo info;
	info.myAddress = anAddress;
	info.myLength = aLength;
	info.myClientID = myNextClientID++;
	myClients.push_back(info);

	return myClients.back();
}

void ClientManager::RemoveClient(const unsigned short aClientID)
{
	for (int i = 0; i < myClients.size(); ++i)
	{
		if (myClients[i].myClientID == aClientID)
		{
			myClients.erase(myClients.begin() + i);
			return;
		}
	}

	//assert(false);
}

const ClientInfo const* ClientManager::GetClient(const unsigned short aClientID)
{
	for (auto& ref : myClients)
	{
		if (ref.myClientID == aClientID)
			return &ref;
	}

	return nullptr;
}

const std::vector<ClientInfo>& ClientManager::GetAllClients()
{
	return myClients;
}

bool ClientManager::HasClient(const unsigned short aClientID)
{
	for (auto& client : myClients)
	{
		if (client.myClientID == aClientID)
			return true;
	}

	return false;
}
