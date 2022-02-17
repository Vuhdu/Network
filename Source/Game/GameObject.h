#pragma once

namespace Tga2D
{
	class CSprite;
}

class GameObject
{
public:
	GameObject();
	~GameObject();

	void Update(CU::InputHandler& anInput);

	void SetClientOwner(const unsigned short aClientID);
	unsigned short GetClientOwner() const;

	void SetGameObjectID(const int aGameObjectID);
	int GetGameObjectID() const;

	void SetPosition(const Tga2D::Vector2f& aPosition);
	const Tga2D::Vector2f& GetPosition() const;
	Tga2D::Vector2f& Position();

	void SetLerpPos(const Tga2D::Vector2f& aPosition);

private:
	Tga2D::CSprite* mySprite = nullptr;

private:
	Tga2D::Vector2f myTargetLerpPos = { 0, 0 };

	unsigned short myOwnerClientID = -1;
	int myGameObjectID = 0;

	float myUpdatePosProgress = 0;
	float myUpdatePosTimer = 0.1f;
};