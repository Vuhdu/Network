#include "stdafx.h"
#include "ApproveConnection.h"
#include "Client.h"

ApproveConnection::ApproveConnection()
	: NetMessage(MessageType::ServerApproveConnection)
{
}

void ApproveConnection::AsServer(sockaddr_in aSocket, int aLength)
{
	// Do nothing
}

void ApproveConnection::AsClient(sockaddr_in aSocket, int aLength)
{
	Client::SetClientID(myClientID);
	INFO_PRINT("Server connetion successful with ID: %i", aLength);
}
