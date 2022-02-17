#pragma once

#undef SendMessage

class Server
{
public:
	static void Init();
	static void Update();
	static void Destroy();

	template<typename T>
	static void SendMessage(T& aBuffer, const unsigned short aClientID, bool aIgnoreGuarantee = false);

	template<typename T>
	static void SendMessageOthers(T& aBuffer, const unsigned short aExceptID, bool aIgnoreGuarantee = false);

	template<typename T>
	static void SendMessageAll(T& aBuffer, bool aIgnoreGuarantee = false);

private:
	inline static SOCKET mySocket;
	inline static sockaddr_in myServerAddress;

	inline static char myBuffer[BUFLEN];

	inline static sockaddr_in myOtherAddress;
	inline static int myOtherAddressLength;

	int myNextMessageID = 1;
};

template<typename T>
inline void Server::SendMessage(T& aBuffer, const unsigned short aClientID, bool aIgnoreGuarantee = false)
{
	static_assert(std::is_base_of<NetMessage, T>::value, "Template type is not a NetMessage.");
	NetMessage* msg = dynamic_cast<NetMessage*>(&aMessage);
	msg->SetMessageID(myNextMessageID++);

	const ClientInfo& clientInfo = ClientManager::GetClient(aClientID);
	auto res = sendto(mySocket, (const char*)&aBuffer, sizeof(T), 0, (const sockaddr*)&clientInfo.myAddress, clientInfo.myLength);
	assert(res != SOCKET_ERROR);

	if (msg->IsGuaranteed() && !aIgnoreGuarantee)
	{
		GuaranteeManager::AwaitResponse(aBuffer, aClientID);
	}
}

template<typename T>
inline void Server::SendMessageOthers(T& aBuffer, const unsigned short aExceptID, bool aIgnoreGuarantee = false)
{
	for (auto& client : ClientManager::GetAllClients())
	{
		if (client.myClientID == aExceptID)
			continue;

		SendMessage(aBuffer, client.myClientID, aIgnoreGuarantee);
	}
}

template<typename T>
inline void Server::SendMessageAll(T& aBuffer, bool aIgnoreGuarantee = false)
{
	for (auto& client : ClientManager::GetAllClients())
	{
		SendMessage(aBuffer, client.myClientID, aIgnoreGuarantee);
	}
}
