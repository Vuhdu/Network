#include "stdafx.h"
#include "PositionUpdateMessage.h"

PositionUpdateMessage::PositionUpdateMessage()
	: NetMessage(MessageType::PositionUpdate)
{
}

void PositionUpdateMessage::AsServer(sockaddr_in aSocket, int aLength)
{
	UpdatePos();
	Server::SendMessageOthers(*this, myClientID);
}

void PositionUpdateMessage::AsClient(sockaddr_in aSocket, int aLength)
{
	UpdatePos();
}

void PositionUpdateMessage::SetGameObjectID(const int aGameObjectID)
{
	memcpy(myBuffer, &aGameObjectID, sizeof(int));
}

void PositionUpdateMessage::SetPosition(const Tga2D::Vector2f& aPos)
{
	memcpy(&myBuffer[sizeof(int)], &aPos, sizeof(Tga2D::Vector2f));
}

void PositionUpdateMessage::UpdatePos()
{
	auto ob = GameObjectManager::GetGameObject(myClientID, GetGameObjectID());
	if (ob)
		ob->SetLerpPos(GetPosition());
	else
		ERROR_PRINT("Missing gameobjects from server");
}

Tga2D::Vector2f PositionUpdateMessage::GetPosition() const
{
	Tga2D::Vector2f pos = *(Tga2D::Vector2f*)&myBuffer[sizeof(int)];
	return pos;
}

int PositionUpdateMessage::GetGameObjectID() const
{
	int id = *(int*)myBuffer;
	return id;
}
