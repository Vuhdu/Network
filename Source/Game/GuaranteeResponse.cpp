#include "stdafx.h"
#include "GuaranteeResponse.h"

GuaranteeResponse::GuaranteeResponse()
	: NetMessage(MessageType::GuaranteeResponse)
{
}

void GuaranteeResponse::AsServer(sockaddr_in aSocket, int aLength)
{
	GuaranteeManager::ReceivedResponse(myMessageID, myClientID);
}

void GuaranteeResponse::AsClient(sockaddr_in aSocket, int aLength)
{
	GuaranteeManager::ReceivedResponse(myMessageID, myClientID);
}
