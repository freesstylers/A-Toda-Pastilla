#pragma once
#include "Entity\Component.h"
class EntitySpawner :public Component
{
public:
	EntitySpawner(json& args);
	~EntitySpawner() {};
	void init(json& j) override;
	void update() override;
	Entity* spawnEntity(Vector3 pos = Vector3(0,0,0), std::string prefab = "");

private:
	std::string defaultPrefab;
	std::list<std::pair<Entity*, int>>items;
	std::vector<int> idsUnused;
};

