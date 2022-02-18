#include "stdafx.h"
#include "InstantiateMessage.h"

InstantiateMessage::InstantiateMessage()
	: NetMessage(MessageType::InstantiateGameObject)
{
	SetGuaranteed(true);
}

void InstantiateMessage::AsServer(sockaddr_in aSocket, int aLength)
{
	auto object = GameObjectManager::AddGameObject(new GameObject());
	int gameObjectID = *(int*)myBuffer;
	object->SetGameObjectID(gameObjectID);
	object->SetClientOwner(myClientID);

	Server::SendMessageOthers(*this, myClientID);
}

void InstantiateMessage::AsClient(sockaddr_in aSocket, int aLength)
{
	auto object = GameObjectManager::AddGameObject(new GameObject());
	int gameObjectID = *(int*)myBuffer;
	object->SetGameObjectID(gameObjectID);
	object->SetClientOwner(myClientID);
}

void InstantiateMessage::SetGameObjectID(const int aID)
{
	memcpy(myBuffer, &aID, sizeof(int));
}
