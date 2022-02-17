#pragma once

#include <vector>
class GameObject;

class FunPark
{
public:
	static void Update();
	
private:
	static void SpawnObject();

private:
	inline static float mySpawnTime = 5;
	inline static float mySpawnProgress = 0;

	inline static std::vector<GameObject*> myObjects;
	inline static std::vector<Tga2D::Vector2f> myVelocity;
};