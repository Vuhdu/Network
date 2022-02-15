#include "stdafx.h"
#include "Server.h"

#include "NetMessage.h"

#include "ClientConnect.h"

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
		INFO_PRINT("Received message from client");
		MessageType type = (MessageType)myBuffer[0];
		bool isGuaranteed = myBuffer[sizeof(MessageType)];

		switch (type)
		{
		case MessageType::ClientConnect:
		{
			ClientConnect* msg = (ClientConnect*)myBuffer;
			msg->AsServer(myOtherAddress, myOtherAddressLength);
		} break;

		case MessageType::ClientDisconnect:

			break;
		}
	}
}

void Server::Destroy()
{
	closesocket(mySocket);
	WSACleanup();
}
