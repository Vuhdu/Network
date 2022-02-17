#pragma once


struct MessageInfo
{
	char myBuffer[576];
	int myBufferSize;
	unsigned short myClientID;
	int myMessageID = -1;

	int myAttempts = 0;
	float myTimeSinceLastAttempt = 0;
};

class GuaranteeManager
{
public:
	template<typename T>
	static void AwaitResponse(T& aBuffer, const unsigned short aClient);

	static void Update();

	static void ReceivedResponse(const int aMessageID, const unsigned short aClientID);

private:
	static void Resend(MessageInfo& someInfo);

private:
	inline static std::unordered_map<unsigned short, std::vector<MessageInfo>> myAwaitingResponses;
	
	inline static float myAttemptTimer = 0.2f;
	inline static int myMaxAttemptCount = 3;
};

template<typename T>
inline void GuaranteeManager::AwaitResponse(T& aBuffer, const unsigned short aClient)
{
	static_assert(std::is_base_of<NetMessage, T>::value, "Template type is not a NetMessage.");
	NetMessage* msg = dynamic_cast<NetMessage*>(&aMessage);

	MessageInfo info;
	info.myClientID = aClient;
	info.myMessageID = msg->GetMessageID();
	info.myBufferSize = sizeof(T);
	memcpy(info.myBuffer, &aBuffer, sizeof(T));
	myAwaitingResponses[aClient].push_back(info);
}
