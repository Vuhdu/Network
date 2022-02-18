#pragma once

constexpr int serverDefaultID = -1;

class Client
{
public:
	static void Init();
	static void Update(CU::InputHandler& anInput);
	static void Destroy();

	template<typename T>
	static void SendMessage(T& aMessage);

	static void SetClientID(const unsigned short aClientID);
	static unsigned short GetClientID();

private:
	friend class GuaranteeManager;

	static void SendMessageInternal(const char* aBuffer, const int aLength);

	static void SendGuaranteeResponse(const int aMessageID);

private:
	inline static SOCKET mySocket;

	inline static sockaddr_in myServerAddress;
	inline static int myServerAddressLength;

	inline static char myBuffer[BUFLEN];

	inline static unsigned short myClientID = serverDefaultID;
	inline static int myNextMessageID = 1;
	inline static int myUniqueID = 0;
};

template<typename T>
inline void Client::SendMessage(T& aMessage)
{
	static_assert(std::is_base_of<NetMessage, T>::value, "Template type is not a NetMessage.");
	NetMessage* msg = dynamic_cast<NetMessage*>(&aMessage);
	msg->SetClientID(myClientID);
	msg->SetMessageID(myNextMessageID++);

	if (msg->GetType() == MessageType::ClientConnect)
		msg->SetMessageID(myUniqueID);

	SendMessageInternal((const char*)&aMessage, sizeof(T));

	if (msg->IsGuaranteed())
		GuaranteeManager::AwaitResponse(aMessage, serverDefaultID);
}
