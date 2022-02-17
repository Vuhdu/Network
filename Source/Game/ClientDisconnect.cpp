#include "stdafx.h"
#include "ClientDisconnect.h"
#include "DestroyObjectMessage.h"

ClientDisconnect::ClientDisconnect()
	: NetMessage(MessageType::ClientDisconnect)
{
}

void ClientDisconnect::AsServer(sockaddr_in aSocket, int aLength)
{
	ClientManager::RemoveClient(myClientID);
	INFO_PRINT("Client %i disconnected.", myClientID);

	std::vector<GameObject*> objectsToRemove;

	for (auto& ob : GameObjectManager::GetAllObjects())
	{
		if (ob->GetClientOwner() == myClientID)
		{
			DestroyObjectMessage msg;
			msg.SetGameObjectID(ob->GetGameObjectID());
			msg.SetClientID(myClientID);
			Server::SendMessageOthers(msg, myClientID);
			objectsToRemove.push_back(ob);
		}
	}

	for (auto& ob : objectsToRemove)
	{
		GameObjectManager::RemoveGameObject(ob);
	}
}

void ClientDisconnect::AsClient(sockaddr_in aSocket, int aLength)
{
	// Hallå?
}
