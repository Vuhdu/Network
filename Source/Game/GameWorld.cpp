#include "stdafx.h"
#include "GameWorld.h"
#include <tga2d/sprite/sprite.h>


#include "Server.h"
#include "Client.h"

CGameWorld::CGameWorld()
{	
}

CGameWorld::~CGameWorld() 
{
}

void CGameWorld::Init()
{
	switch (myType)
	{
	case NetworkType::Client:
		myClient->Init();
		break;
	case NetworkType::Server:
		myServer->Init();
		break;
	default:
		break;
	}
}

void CGameWorld::Update(CU::InputHandler& anInput, const float aDeltaTime)
{
	switch (myType)
	{
	case NetworkType::Client:
		myClient->Update();
		break;
	case NetworkType::Server:
		myServer->Update();
		break;
	default:
		break;
	}
}

void CGameWorld::Render()
{
}

void CGameWorld::SetNetworkType(const NetworkType aType)
{
	myType = aType;
	switch (myType)
	{
	case NetworkType::Client:
		myClient = new Client();
		break;
	case NetworkType::Server:
		myServer = new Server();
		break;
	default:
		break;
	}
}
