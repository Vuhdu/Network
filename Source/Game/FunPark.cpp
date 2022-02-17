#include "stdafx.h"
#include "FunPark.h"
#include "GameObject.h"

#include <unordered_set>
#include "DestroyObjectMessage.h"
#include "InstantiateMessage.h"

void FunPark::Update()
{
	float delta = Tga2D::CEngine::GetInstance()->GetDeltaTime();

	mySpawnProgress += delta;
	if (mySpawnProgress >= mySpawnTime)
	{
		mySpawnProgress = 0;
		SpawnObject();
	}

	std::unordered_set<GameObject*> toRemove;
	for (int i = 0; i < myObjects.size(); ++i)
	{
		GameObject* ob = myObjects[i];
		Tga2D::Vector2f& velocity = myVelocity[i];

		float angle = atan2(velocity.y, velocity.x);
		angle += ((float)rand() / (float)RAND_MAX) * (0.25 * delta);

		velocity = { cos(angle), sin(angle) };

		ob->SetPosition(ob->GetPosition() + velocity * delta * 0.5f);

		if (ob->GetPosition().x < 0 || ob->GetPosition().x > 1)
			velocity.x *= -1;

		if (ob->GetPosition().y < 0 ||  ob->GetPosition().y > 1)
			velocity.y *= -1;

		for (auto& second : myObjects)
		{
			CU::Vector2f deltaPos;
			deltaPos.x = second->GetPosition().x - ob->GetPosition().x;
			deltaPos.y = second->GetPosition().y - ob->GetPosition().y;

			if (ob == second)
				continue;
			
			if (deltaPos.Length() < (0.05f * 2))
			{
				toRemove.insert(ob);
				toRemove.insert(second);
			}
		}
	}

	for (auto& ob : toRemove)
	{
		for (int i = 0; i < myObjects.size(); ++i)
		{
			if (myObjects[i] == ob)
			{
				myObjects.erase(myObjects.begin() + i);
				myVelocity.erase(myVelocity.begin() + i);
				break;
			}
		}

		DestroyObjectMessage msg;
		msg.SetGameObjectID(ob->GetGameObjectID());
		msg.SetClientID(ob->GetClientOwner());
		Server::SendMessageAll(msg);
		
		GameObjectManager::RemoveGameObject(ob);

	}
}

void FunPark::SpawnObject()
{
	if (myObjects.size() >= 10)
		return;

	myObjects.push_back(GameObjectManager::AddGameObject(new GameObject()));
	myVelocity.push_back({ (float)rand() / (float)RAND_MAX, (float)rand() / (float)RAND_MAX });
	myVelocity.back().Normalize();

	InstantiateMessage msg;
	msg.SetGameObjectID(myObjects.back()->GetGameObjectID());
	msg.SetClientID(Client::GetClientID());
	Server::SendMessageAll(msg);
}
