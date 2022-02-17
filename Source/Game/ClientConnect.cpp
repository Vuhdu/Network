#include "stdafx.h"
#include "ClientConnect.h"
#include "ApproveConnection.h"
#include "InstantiateMessage.h"

ClientConnect::ClientConnect()
	: NetMessage(MessageType::ClientConnect)
{ }

void ClientConnect::AsServer(sockaddr_in aSocket, int aLength)
{
	const ClientInfo& info = ClientManager::AddClient(aSocket, aLength);

	ApproveConnection msg;
	msg.SetClientID(info.myClientID);
	INFO_PRINT("ID: %i", info.myClientID);
	Server::SendMessage(msg, info.myClientID);

	for (auto& ob : GameObjectManager::GetAllObjects())
	{
		InstantiateMessage msg;
		msg.SetGameObjectID(ob->GetGameObjectID());
		msg.SetClientID(ob->GetClientOwner());
		Server::SendMessage(msg, info.myClientID);
	}
}

void ClientConnect::AsClient(sockaddr_in aSocket, int aLength)
{
	// Hallå ?
}

Ping::Ping() : NetMessage(MessageType::Ping)
{
}

void Ping::AsServer(sockaddr_in aSocket, int aLength)
{
	INFO_PRINT("Ping as server");
}

void Ping::AsClient(sockaddr_in aSocket, int aLength)
{
	INFO_PRINT("Ping as client");
}
