#pragma once
#include "Entity\Component.h"
class EntitySpawner :public Component
{
public:
	EntitySpawner(json& args);
	~EntitySpawner() {};
	void init(json& j) override;
	void update() override;
	Entity* spawnEntity(std::string prefab = "");

private:
	std::string defaultPrefab;
	std::list<Entity*>items;
};

