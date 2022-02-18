#pragma once

#undef SendMessage

class Server
{
public:
	static void Init();
	static void Update();
	static void Destroy();

	template<typename T>
	static void SendMessage(T& aBuffer, const unsigned short aClientID);

	template<typename T>
	static void SendMessageOthers(T& aBuffer, const unsigned short aExceptID);

	template<typename T>
	static void SendMessageAll(T& aBuffer);

	static void TimeoutClient(const unsigned short aClientID);

private:
	friend class GuaranteeManager;

	static void SendMessageInternal(const char* aBuffer, const int aLength, const unsigned short aClientID);

	static void SendGuaranteeResponse(const unsigned short aClientID, const int aMessageID);

private:
	inline static SOCKET mySocket;
	inline static sockaddr_in myServerAddress;

	inline static char myBuffer[BUFLEN];

	inline static sockaddr_in myOtherAddress;
	inline static int myOtherAddressLength;

	inline static int myNextMessageID = 1;
};

template<typename T>
inline void Server::SendMessage(T& aBuffer, const unsigned short aClientID)
{
	static_assert(std::is_base_of<NetMessage, T>::value, "Template type is not a NetMessage.");
	NetMessage* msg = dynamic_cast<NetMessage*>(&aBuffer);
	msg->SetMessageID(myNextMessageID++);

	SendMessageInternal((const char*)&aBuffer, sizeof(T), aClientID);

	if (msg->IsGuaranteed())
	{
		GuaranteeManager::AwaitResponse(aBuffer, aClientID);
	}
}

template<typename T>
inline void Server::SendMessageOthers(T& aBuffer, const unsigned short aExceptID)
{
	for (auto& client : ClientManager::GetAllClients())
	{
		if (client.myClientID == aExceptID)
			continue;

		SendMessage(aBuffer, client.myClientID);
	}
}

template<typename T>
inline void Server::SendMessageAll(T& aBuffer)
{
	for (auto& client : ClientManager::GetAllClients())
	{
		SendMessage(aBuffer, client.myClientID);
	}
}
