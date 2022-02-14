#pragma once

#undef SendMessage

class Server
{
public:
	static void Init();
	static void Update();

	template<typename T>
	static void SendMessage(T& aBuffer, const unsigned short aClientID);

private:
	inline static SOCKET mySocket;
	inline static sockaddr_in myServerAddress;

	inline static char myBuffer[BUFLEN];
	inline static int myBufferLength;
	inline static sockaddr_in myOtherAddress;
	inline static int myOtherAddressLength;
};

template<typename T>
inline void Server::SendMessage(T& aBuffer, const unsigned short aClientID)
{
	const ClientInfo& clientInfo = ClientManager::GetClient(aClientID);
	auto res = sendto(mySocket, (const char*)&aBuffer, sizeof(T), 0, (const sockaddr*)&clientInfo.myAddress, clientInfo.myLength);
	assert(res != SOCKET_ERROR);
}
