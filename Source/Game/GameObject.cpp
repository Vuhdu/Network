#include "stdafx.h"
#include "GameObject.h"
#include "tga2d/sprite/sprite.h"

#include "PositionUpdateMessage.h"

#include "Mathcu.hpp"

GameObject::GameObject()
{
	mySprite = new Tga2D::CSprite("sprites/player.dds");
	mySprite->SetPivot({ 0.5f, 0.5f });
	mySprite->SetPosition({ 0.5f, 0.5f });
}

GameObject::~GameObject()
{
	delete mySprite;
	mySprite = nullptr;
}

void GameObject::Update(CU::InputHandler& anInput)
{
	static float lerpAmount = 0.007;

	if (myOwnerClientID == Client::GetClientID())
	{
		Tga2D::Vector2f movement;

		float delta = Tga2D::CEngine::GetInstance()->GetDeltaTime();

		if (anInput.IsKeyPressed(CU::eKeyCode::W))
		{
			movement.y -= 1;
		}

		if (anInput.IsKeyPressed(CU::eKeyCode::S))
		{
			movement.y += 1;
		}
		
		if (anInput.IsKeyPressed(CU::eKeyCode::A))
		{
			movement.x -= 1;
		}

		if (anInput.IsKeyPressed(CU::eKeyCode::D))
		{
			movement.x += 1;
		}

		movement.Normalize();

		float speed = 0.5f;
		mySprite->SetPosition(mySprite->GetPosition() + movement * speed * delta);

		myUpdatePosProgress += delta;
		if (myUpdatePosProgress >= myUpdatePosTimer)
		{
			myUpdatePosProgress = 0;
			PositionUpdateMessage msg;
			msg.SetGameObjectID(myGameObjectID);
			msg.SetPosition(mySprite->GetPosition());
			Client::SendMessage(msg);
		}
	}
	else
	{

		float x = CU::Lerp(mySprite->GetPosition().x, myTargetLerpPos.x, lerpAmount);
		float y = CU::Lerp(mySprite->GetPosition().y, myTargetLerpPos.y, lerpAmount);
		mySprite->SetPosition({ x, y });
	}

	mySprite->Render();
}

void GameObject::SetClientOwner(const unsigned short aClientID)
{
	myOwnerClientID = aClientID;
}

unsigned short GameObject::GetClientOwner() const
{
	return myOwnerClientID;
}

void GameObject::SetGameObjectID(const int aGameObjectID)
{
	myGameObjectID = aGameObjectID;
}

int GameObject::GetGameObjectID() const
{
	return myGameObjectID;
}

void GameObject::SetPosition(const Tga2D::Vector2f& aPosition)
{
	mySprite->SetPosition(aPosition);
}

void GameObject::SetLerpPos(const Tga2D::Vector2f& aPosition)
{
	myTargetLerpPos = aPosition;
}
