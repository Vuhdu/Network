#pragma once

#include <vector>

class GameObject;

class GameObjectManager
{
public:

	static GameObject* AddGameObject(GameObject* anObject);
	static void RemoveGameObject(GameObject* anObject);
	static void Update(CU::InputHandler& anInput);

	static GameObject* GetGameObject(const unsigned short aClientID, const int aGameObjectID);

	static const std::vector<GameObject*>& GetAllObjects();

private:
	inline static int myNextGameObjectID = 1;
	inline static std::vector<GameObject*> myObjects;
};