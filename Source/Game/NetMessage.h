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
	DestroyGameObject,

	GuaranteeResponse
};

class NetMessage
{
protected:
	MessageType myType = MessageType::None;
	bool myIsGuaranteed = false;
	int myMessageID = -1;
	unsigned short myClientID = -1;
	char myBuffer[552];

public:
	NetMessage() = delete;
	NetMessage(NetMessage&) = delete;

	NetMessage(MessageType aType);

	MessageType GetType() const;

	unsigned short GetClientID() const;
	void SetClientID(const unsigned short aClientID);

	int GetMessageID() const;
	void SetMessageID(const int aMessageID);
	
	void SetGuaranteed(const bool aValue);
	bool IsGuaranteed() const;

	virtual void AsServer(sockaddr_in aSocket, int aLength) = 0;
	virtual void AsClient(sockaddr_in aSocket, int aLength) = 0;
};

