#include "stdafx.h"
#include "NetMessage.h"

NetMessage::NetMessage()
{
}

unsigned short NetMessage::GetClientID() const
{
	return myClientID;
}

void NetMessage::SetClientID(const unsigned short aClientID)
{
	myClientID = aClientID;
}

void NetMessage::SetGuaranteed(const bool aValue)
{
	myIsGuaranteed = aValue;
}

bool NetMessage::IsGuaranteed() const
{
	return myIsGuaranteed;
}
