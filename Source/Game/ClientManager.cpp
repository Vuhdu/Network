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

	assert(false);
}

const ClientInfo& ClientManager::GetClient(const unsigned short aClientID)
{
	for (auto& ref : myClients)
	{
		if (ref.myClientID == aClientID)
			return ref;
	}
}

const std::vector<ClientInfo>& ClientManager::GetAllClients()
{
	return myClients;
}
