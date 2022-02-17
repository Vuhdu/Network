#pragma once

enum class MessageType
{
	None,
	Ping,

	ClientConnect,
	ClientDisconnect,
	ServerApproveConnection,

	InstantiateGameObject,
	PositionUpdate,
	DestroyGameObject
};

class NetMessage
{
protected:
	MessageType myType = MessageType::None;
	bool myIsGuaranteed = false;
	unsigned short myClientID = -1;
	char myBuffer[552];

public:
	NetMessage() = delete;
	NetMessage(NetMessage&) = delete;

	NetMessage(MessageType aType);

	unsigned short GetClientID() const;
	void SetClientID(const unsigned short aClientID);

	void SetGuaranteed(const bool aValue);
	bool IsGuaranteed() const;

	virtual void AsServer(sockaddr_in aSocket, int aLength) = 0;
	virtual void AsClient(sockaddr_in aSocket, int aLength) = 0;
};

