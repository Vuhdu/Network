#pragma once

class NetworkManager
{
public:
	NetworkManager() = default;
	~NetworkManager() = default;

	static const char* GetServerIP();
	static unsigned short GetPort();


private:
	inline static const char* myServerIP = "127.0.0.1";
	inline static unsigned short myPort = 13371;
	
};

