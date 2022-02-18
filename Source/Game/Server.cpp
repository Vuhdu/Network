#include "stdafx.h"
#include "Server.h"

#include "NetMessage.h"

#include "ClientConnect.h"
#include "ClientDisconnect.h"

#include "InstantiateMessage.h"
#include "PositionUpdateMessage.h"
#include "DestroyObjectMessage.h"
#include "GuaranteeResponse.h"

void Server::Init()
{
	WSADATA wsa;
	myOtherAddressLength = sizeof(myOtherAddress);

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		assert(false);

	mySocket = socket(AF_INET, SOCK_DGRAM, 0);
	if (mySocket == INVALID_SOCKET)
	{
		WSACleanup();
		assert(false);
	}

	myServerAddress.sin_family = AF_INET;
	myServerAddress.sin_addr.s_addr = INADDR_ANY;
	myServerAddress.sin_port = htons(PORT);

	auto res = bind(mySocket, (struct sockaddr*)&myServerAddress, sizeof(myServerAddress));
	if (res == SOCKET_ERROR)
	{
		closesocket(mySocket);
		WSACleanup();
		assert(false);
	}

	u_long mode = TRUE;
	ioctlsocket(mySocket, FIONBIO, &mode);

	INFO_PRINT("Server started.");
}

void Server::Update()
{
	memset(myBuffer, '\0', BUFLEN);
	
	if (recvfrom(mySocket, myBuffer, BUFLEN, 0, (struct sockaddr*)&myOtherAddress, &myOtherAddressLength) != SOCKET_ERROR)
	{
		//INFO_PRINT("Received message from client");

		const char* buf = (const char*)&myBuffer;
		NetMessage* net_msg = (NetMessage*)buf;

		MessageType type = net_msg->GetType();
		bool isGuaranteed = net_msg->IsGuaranteed();
		int messageID = net_msg->GetMessageID();
		unsigned short clientID = net_msg->GetClientID();
		if (type != MessageType::ClientConnect && !ClientManager::HasClient(clientID))
		{
			return;
		}

		if (GuaranteeManager::IsHandled(clientID, messageID) && isGuaranteed)
		{
			SendGuaranteeResponse(clientID, messageID);
			INFO_PRINT("Message already handled from client: %i with message id: %i", clientID, messageID);
			return;
		}

		if (isGuaranteed)
		{
			SendGuaranteeResponse(clientID, messageID);
			GuaranteeManager::AddHandledMessage(clientID, messageID);
			INFO_PRINT("Received a guaranteed message from client: %i with message id: %i", clientID, messageID);
		}

		switch (type)
		{
		case MessageType::ClientConnect:
		{
			ClientConnect* msg = (ClientConnect*)buf;
			msg->AsServer(myOtherAddress, myOtherAddressLength);
		} break;

		case MessageType::ClientDisconnect:
		{
			ClientDisconnect* msg = (ClientDisconnect*)buf;
			msg->AsServer(myOtherAddress, myOtherAddressLength);
		} break;

		case MessageType::InstantiateGameObject:
		{
			InstantiateMessage* msg = (InstantiateMessage*)buf;
			msg->AsServer(myOtherAddress, myOtherAddressLength);
		}break;

		case MessageType::PositionUpdate:
		{
			PositionUpdateMessage* msg = (PositionUpdateMessage*)buf;
			msg->AsServer(myOtherAddress, myOtherAddressLength);
		}break;

		case MessageType::DestroyGameObject:
		{
			DestroyObjectMessage* msg = (DestroyObjectMessage*)buf;
			msg->AsServer(myOtherAddress, myOtherAddressLength);
		}break;

		case MessageType::GuaranteeResponse:
		{
			GuaranteeResponse* msg = (GuaranteeResponse*)buf;
			msg->AsServer(myOtherAddress, myOtherAddressLength);
		}break;
		}
	}
}

void Server::Destroy()
{
	closesocket(mySocket);
	WSACleanup();
}

void Server::TimeoutClient(const unsigned short aClientID)
{
	INFO_PRINT("Timedout client with ID: %i.", aClientID);
	ClientManager::RemoveClient(aClientID);
}

void Server::SendMessageInternal(const char* aBuffer, const int aLength, const unsigned short aClientID)
{
	const ClientInfo const* clientInfo = ClientManager::GetClient(aClientID);

	int result;
	
	if (clientInfo)
		result = sendto(mySocket, aBuffer, aLength, 0, (const sockaddr*)&clientInfo->myAddress, clientInfo->myLength);
	else
		result = sendto(mySocket, aBuffer, aLength, 0, (const sockaddr*)&myOtherAddress, myOtherAddressLength);

	assert(result != SOCKET_ERROR);
}

void Server::SendGuaranteeResponse(const unsigned short aClientID, const int aMessageID)
{
	GuaranteeResponse msg;
	msg.SetMessageID(aMessageID);
	msg.SetClientID(Client::GetClientID());
	SendMessageInternal((const char*)&msg, sizeof(GuaranteeResponse), aClientID);
}
