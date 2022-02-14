#include "stdafx.h"
#include "ClientConnect.h"
#include "ApproveConnection.h"

void ClientConnect::AsServer(sockaddr_in aSocket, int aLength)
{
	const ClientInfo& info = ClientManager::AddClient(aSocket, aLength);

	ApproveConnection msg;
	msg.SetClientID(info.myClientID);
	Server::SendMessage(msg, info.myClientID);
}

void ClientConnect::AsClient(sockaddr_in aSocket, int aLength)
{
	// Hallå ?
}
