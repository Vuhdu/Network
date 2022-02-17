#include "stdafx.h"
#include "DestroyObjectMessage.h"

DestroyObjectMessage::DestroyObjectMessage()
	: NetMessage(MessageType::DestroyGameObject)
{
}

void DestroyObjectMessage::AsServer(sockaddr_in aSocket, int aLength)
{
	RemoveObject();
	Server::SendMessageOthers(*this, myClientID);
}

void DestroyObjectMessage::AsClient(sockaddr_in aSocket, int aLength)
{
	RemoveObject();
}

void DestroyObjectMessage::SetGameObjectID(const int aID)
{
	memcpy(myBuffer, &aID, sizeof(int));
}

int DestroyObjectMessage::GetGameObjectID() const
{
	int id = *(int*)myBuffer;
	return id;
}

void DestroyObjectMessage::RemoveObject()
{
	auto ob = GameObjectManager::GetGameObject(myClientID, GetGameObjectID());
	GameObjectManager::RemoveGameObject(ob);
}
