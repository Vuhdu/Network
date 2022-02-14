#pragma once
class Client
{
public:
	static void Init();
	static void Update();

private:
	inline static SOCKET mySocket;
};

