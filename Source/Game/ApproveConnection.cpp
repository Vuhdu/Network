#include "stdafx.h"
#include "ApproveConnection.h"
#include "Client.h"

#include "InstantiateMessage.h"

ApproveConnection::ApproveConnection()
	: NetMessage(MessageType::ServerApproveConnection)
{
	SetGuaranteed(true);
}

void ApproveConnection::AsServer(sockaddr_in aSocket, int aLength)
{
	// Do nothing
}

void ApproveConnection::AsClient(sockaddr_in aSocket, int aLength)
{
	Client::SetClientID(myClientID);
	INFO_PRINT("Connection successfull with ID: %i", myClientID);

	GameObject* ob = GameObjectManager::AddGameObject(new GameObject());
	ob->SetClientOwner(myClientID);

	InstantiateMessage msg;
	msg.SetGameObjectID(ob->GetGameObjectID());
	Client::SendMessage(msg);
}
