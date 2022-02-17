#include "stdafx.h"
#include "GuaranteeManager.h"
#include "NetMessage.h"

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
			}
		}
	}

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

void GuaranteeManager::Resend(MessageInfo& someInfo)
{
	// FACK
}
