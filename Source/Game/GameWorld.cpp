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
	switch (myType)
	{
	case NetworkType::Client:
		Client::Destroy();
		break;

	case NetworkType::Server:
		Server::Destroy();
		break;
	}
}

void CGameWorld::Init()
{
	switch (myType)
	{
	case NetworkType::Client:
		Client::Init();
		break;
	case NetworkType::Server:
		Server::Init();
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
		Client::Update(anInput);
		break;
	case NetworkType::Server:
		Server::Update();
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
}
