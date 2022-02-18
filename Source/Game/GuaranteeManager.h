#pragma once

#include <set>

struct MessageInfo
{
	char myBuffer[576];
	int myBufferSize;
	unsigned short myClientID;
	int myMessageID = -1;

	int myAttempts = 0;
	float myTimeSinceLastAttempt = 0;

	bool operator==(const MessageInfo& anOther) const
	{
		return myClientID == anOther.myClientID && myMessageID == anOther.myMessageID;
	}
};

class GuaranteeManager
{
public:
	template<typename T>
	static void AwaitResponse(T& aBuffer, const unsigned short aClient);

	static void Update();

	static void ReceivedResponse(const int aMessageID, const unsigned short aClientID);

	static bool IsHandled(const unsigned short aClientID, const int aMessageID);

	static void AddHandledMessage(const unsigned short aClientID, const int aMessageID);

private:
	static void Resend(MessageInfo& someInfo);
	static void Timeout(MessageInfo& someInfo);

private:
	inline static std::unordered_map<unsigned short, std::vector<MessageInfo>> myAwaitingResponses;
	inline static std::vector<unsigned short> myToRemove;

	inline static std::set<std::pair<unsigned short, int>> myHandledMessages;
	
	inline static float myAttemptTimer = .2f;
	inline static int myMaxAttemptCount = 10;
};

template<typename T>
inline void GuaranteeManager::AwaitResponse(T& aBuffer, const unsigned short aClient)
{
	static_assert(std::is_base_of<NetMessage, T>::value, "Template type is not a NetMessage.");
	NetMessage* msg = dynamic_cast<NetMessage*>(&aBuffer);

	INFO_PRINT("Sent guaranteed message.");

	MessageInfo info;
	info.myClientID = aClient;
	info.myMessageID = msg->GetMessageID();
	info.myBufferSize = sizeof(T);
	memcpy(info.myBuffer, &aBuffer, sizeof(T));
	myAwaitingResponses[aClient].push_back(info);
}
