#include "stdafx.h"
#include "NetMessage.h"

NetMessage::NetMessage(MessageType aType)
{
	myType = aType;
}

unsigned short NetMessage::GetClientID() const
{
	return myClientID;
}

void NetMessage::SetClientID(const unsigned short aClientID)
{
	myClientID = aClientID;
}

int NetMessage::GetMessageID() const
{
	return myMessageID;
}

void NetMessage::SetMessageID(const int aMessageID)
{
	myMessageID = aMessageID;
}

void NetMessage::SetGuaranteed(const bool aValue)
{
	myIsGuaranteed = aValue;
}

bool NetMessage::IsGuaranteed() const
{
	return myIsGuaranteed;
}
