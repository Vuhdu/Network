#include "stdafx.h"
#include "GuaranteeManager.h"
#include "NetMessage.h"
#include "GameWorld.h"

void GuaranteeManager::Update()
{
	float delta = Tga2D::CEngine::GetInstance()->GetDeltaTime();

	for (auto& entry : myAwaitingResponses)
	{
		for (auto& info : entry.second)
		{
			info.myTimeSinceLastAttempt += delta;

			if (info.myTimeSinceLastAttempt >= myAttemptTimer)
			{
				Resend(info);
				info.myTimeSinceLastAttempt = 0;
			}
		}
	}

	for (auto& clientID : myToRemove)
	{
		myAwaitingResponses.erase(clientID);
	}
	myToRemove.clear();
}

void GuaranteeManager::ReceivedResponse(const int aMessageID, const unsigned short aClientID)
{
	for (auto& info : myAwaitingResponses[aClientID])
	{
		if (info.myMessageID == aMessageID)
		{
			myAwaitingResponses[aClientID].erase(std::remove(myAwaitingResponses[aClientID].begin(), myAwaitingResponses[aClientID].end(), info));
			return;
		}
	}
}

bool GuaranteeManager::IsHandled(const unsigned short aClientID, const int aMessageID)
{
	return myHandledMessages.count({ aClientID, aMessageID });
}

void GuaranteeManager::AddHandledMessage(const unsigned short aClientID, const int aMessageID)
{
	myHandledMessages.insert({ aClientID, aMessageID });
}

void GuaranteeManager::Resend(MessageInfo& someInfo)
{
	INFO_PRINT("Resending guaranteed message");
	if (CGameWorld::GetNetType() == NetworkType::Server)
	{
		Server::SendMessageInternal(someInfo.myBuffer, someInfo.myBufferSize, someInfo.myClientID);
	}

	if (CGameWorld::GetNetType() == NetworkType::Client)
	{
		Client::SendMessageInternal(someInfo.myBuffer, someInfo.myBufferSize);
	}
	someInfo.myAttempts++;

	if (someInfo.myAttempts > myMaxAttemptCount)
	{
		Timeout(someInfo);
	}
}

void GuaranteeManager::Timeout(MessageInfo& someInfo)
{
	INFO_PRINT("Timed out.");
	if (CGameWorld::GetNetType() == NetworkType::Client)
	{
		Client::Destroy();
		myToRemove.push_back(someInfo.myClientID);
	}

	if (CGameWorld::GetNetType() == NetworkType::Server)
	{
		myToRemove.push_back(someInfo.myClientID);
	}
}
