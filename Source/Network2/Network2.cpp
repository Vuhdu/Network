
#include <iostream>

#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

#include <Windows.h>

int main()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		std::cout << "DENIED" << std::endl;

    std::cout << "Hello World!\n";
}
