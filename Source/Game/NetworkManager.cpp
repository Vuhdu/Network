#include "stdafx.h"
#include "NetworkManager.h"

const char* NetworkManager::GetServerIP()
{
    return myServerIP;
}

unsigned short NetworkManager::GetPort()
{
    return myPort;
}
