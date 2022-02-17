#pragma once

constexpr int serverDefaultID = -1;

class Client
{
public:
	static void Init();
	static void Update(CU::InputHandler& anInput);
	static void Destroy();

	template<typename T>
	static void SendMessage(T& aMessage, bool aIgnoreGuarantee = false);

	static void SetClientID(const unsigned short aClientID);
	static unsigned short GetClientID();

private:
	inline static SOCKET mySocket;

	inline static sockaddr_in myServerAddress;
	inline static int myServerAddressLength;

	inline static char myBuffer[BUFLEN];

	inline static unsigned short myClientID = serverDefaultID;
	inline static int myNextMessageID = 1;
};

template<typename T>
inline void Client::SendMessage(T& aMessage, bool aIgnoreGuarantee = false)
{
	static_assert(std::is_base_of<NetMessage, T>::value, "Template type is not a NetMessage.");
	NetMessage* msg = dynamic_cast<NetMessage*>(&aMessage);
	msg->SetClientID(myClientID);
	msg->SetMessageID(myNextMessageID++);

	auto res = sendto(mySocket, (const char*)&aMessage, sizeof(T), 0, (struct sockaddr*)&myServerAddress, myServerAddressLength);
	assert(res != SOCKET_ERROR);

	if (msg->IsGuaranteed() && !aIgnoreGuarantee)
		GuaranteeManager::AwaitResponse(aMessage, serverDefaultID);
}
