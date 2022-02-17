#include "stdafx.h"
#include "GameObjectManager.h"
#include "GameObject.h"

GameObject* GameObjectManager::AddGameObject(GameObject* anObject)
{
	myObjects.push_back(anObject);
	anObject->SetGameObjectID(myNextGameObjectID++);
	return anObject;
}

void GameObjectManager::RemoveGameObject(GameObject* anObject)
{
	myObjects.erase(std::remove(myObjects.begin(), myObjects.end(), anObject));
	delete anObject;
}

void GameObjectManager::Update(CU::InputHandler& anInput)
{
	for (auto& ob : myObjects)
	{
		ob->Update(anInput);
	}
}

GameObject* GameObjectManager::GetGameObject(const unsigned short aClientID, const int aGameObjectID)
{
	for (auto& ob : myObjects)
	{
		if (ob->GetGameObjectID() == aGameObjectID && ob->GetClientOwner() == aClientID)
			return ob;
	}

	// mabe sync objects if missmatch? idk. Id ont do networ prgokrgmming.
	return nullptr;
}

const std::vector<GameObject*>& GameObjectManager::GetAllObjects()
{
	return myObjects;
}
