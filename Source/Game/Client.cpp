#include "stdafx.h"
#include "Client.h"

#include "ClientConnect.h"
#include "ApproveConnection.h"
#include "ClientDisconnect.h"
#include "InstantiateMessage.h"
#include "PositionUpdateMessage.h"
#include "DestroyObjectMessage.h"
#include "GuaranteeResponse.h"

void Client::Init()
{
	srand(time(0));
	myUniqueID = rand();

	WSADATA wsa;
	myServerAddressLength = sizeof(myServerAddress);

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		assert(false);

	mySocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	assert(mySocket != INVALID_SOCKET);

	memset((char*)&myServerAddress, 0, sizeof(myServerAddress));
	myServerAddress.sin_family = AF_INET;
	myServerAddress.sin_port = htons(PORT);
	myServerAddress.sin_addr.S_un.S_addr = inet_addr(SERVER);

	u_long mode = TRUE;
	int result = ioctlsocket(mySocket, FIONBIO, &mode);
	assert(result == 0);

	ClientConnect msg;
	SendMessage(msg);

	INFO_PRINT("Client is connecting...");
}

void Client::Update(CU::InputHandler& anInput)
{
	memset(myBuffer, '\0', BUFLEN);

	if (recvfrom(mySocket, myBuffer, BUFLEN, 0, (struct sockaddr*)&myServerAddress, &myServerAddressLength) != SOCKET_ERROR)
	{
		const char* buf = (const char*)&myBuffer;
		NetMessage* net_msg = (NetMessage*)buf;

		MessageType type = net_msg->GetType();
		bool isGuaranteed = net_msg->IsGuaranteed();
		int messageID = net_msg->GetMessageID();
		unsigned short clientID = net_msg->GetClientID();

		if (GuaranteeManager::IsHandled(clientID, messageID) && isGuaranteed)
		{
			SendGuaranteeResponse(messageID);
			INFO_PRINT("Message already handled from server with message id: %i", messageID);
			return;
		}

		if (isGuaranteed)
		{
			SendGuaranteeResponse(messageID);
			GuaranteeManager::AddHandledMessage(clientID, messageID);
			INFO_PRINT("Received a guaranteed message from server with message id: %i", messageID);
		}

		switch (type)
		{
		case MessageType::ServerApproveConnection:
		{
			ApproveConnection* msg = (ApproveConnection*)buf;
			msg->AsClient(myServerAddress, myServerAddressLength);
		} break;

		case MessageType::InstantiateGameObject:
		{
			InstantiateMessage* msg = (InstantiateMessage*)buf;
			msg->AsClient(myServerAddress, myServerAddressLength);
		}break;

		case MessageType::PositionUpdate:
		{
			PositionUpdateMessage* msg = (PositionUpdateMessage*)buf;
			msg->AsClient(myServerAddress, myServerAddressLength);
		}break;

		case MessageType::DestroyGameObject:
		{
			DestroyObjectMessage* msg = (DestroyObjectMessage*)buf;
			msg->AsClient(myServerAddress, myServerAddressLength);
		}break;

		case MessageType::GuaranteeResponse:
		{
			GuaranteeResponse* msg = (GuaranteeResponse*)buf;
			msg->AsClient(myServerAddress, myServerAddressLength);
		}break;
		}
	}
}

void Client::Destroy()
{
	ClientDisconnect msg;
	SendMessage(msg);

	closesocket(mySocket);
	WSACleanup();
}

void Client::SetClientID(const unsigned short aClientID)
{
	myClientID = aClientID;
}

unsigned short Client::GetClientID()
{
	return myClientID;
}

void Client::SendMessageInternal(const char* aBuffer, const int aLength)
{
	auto res = sendto(mySocket, aBuffer, aLength, 0, (struct sockaddr*)&myServerAddress, myServerAddressLength);
	assert(res != SOCKET_ERROR);
}

void Client::SendGuaranteeResponse(const int aMessageID)
{
	GuaranteeResponse msg;
	msg.SetMessageID(aMessageID);
	msg.SetClientID(Client::GetClientID());
	SendMessageInternal((const char*)&msg, sizeof(GuaranteeResponse));
}
