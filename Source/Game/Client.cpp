#include "stdafx.h"
#include "Client.h"

#include "ClientConnect.h"
#include "ApproveConnection.h"
#include "ClientDisconnect.h"
#include "InstantiateMessage.h"
#include "PositionUpdateMessage.h"
#include "DestroyObjectMessage.h"

void Client::Init()
{
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
		MessageType type = *(MessageType*)&buf[8];
		INFO_PRINT("Received message from server");

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
