#include "stdafx.h"
#include "NetworkManager.h"

const char* NetworkManager::GetServerIP()
{
    return myServerIP;
}

int NetworkManager::GetPort()
{
    return myPort;
}
