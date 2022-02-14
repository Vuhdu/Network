#include "stdafx.h"
#include "Server.h"

#include "NetMessage.h"

#include "ClientConnect.h"

void Server::Init()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		assert(false);

	mySocket = socket(AF_INET, SOCK_DGRAM, 0);
	assert(mySocket != INVALID_SOCKET);

	myServerAddress.sin_family = AF_INET;
	myServerAddress.sin_addr.s_addr = INADDR_ANY;
	myServerAddress.sin_port = htons(NetworkManager::GetPort());

	auto res = bind(mySocket, (struct sockaddr*)&myServerAddress, sizeof(myServerAddress));
	assert(res!= SOCKET_ERROR);

	u_long mode = TRUE;
	ioctlsocket(mySocket, FIONBIO, &mode);

	INFO_PRINT("Server started.");
}

void Server::Update()
{
	memset(myBuffer, '\0', BUFLEN);
	if (recvfrom(mySocket, myBuffer, BUFLEN, 0, (struct sockaddr*)&myOtherAddress, &myOtherAddressLength))
	{
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