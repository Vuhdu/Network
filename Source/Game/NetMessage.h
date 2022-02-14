#pragma once

enum class MessageType
{
	None,
	ClientConnect,
	ClientDisconnect
};

class NetMessage
{
public:
	NetMessage();

	unsigned short GetClientID() const;
	void SetClientID(const unsigned short aClientID);

	void SetGuaranteed(const bool aValue);
	bool IsGuaranteed() const;

	virtual void AsServer(sockaddr_in aSocket, int aLength) = 0;
	virtual void AsClient(sockaddr_in aSocket, int aLength) = 0;

protected:
	MessageType myType = MessageType::None;
	bool myIsGuaranteed = false;
	unsigned short myClientID = -1;
	char myBuffer[568];
};

