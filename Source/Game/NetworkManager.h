#pragma once

class NetworkManager
{
public:
	NetworkManager() = default;
	~NetworkManager() = default;

	static const char* GetServerIP();
	static int GetPort();


private:
	
	inline static const char* myServerIP = "127.0.0.1";
	inline static int myPort = 13370;
	
};

