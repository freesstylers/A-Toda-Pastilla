#pragma once

#include "Entity\Component.h"
#include "EntitySpawner.h"

class SpawnerMejora : public EntitySpawner
{
public:
	SpawnerMejora(json& args);
	~SpawnerMejora();
	virtual void update() override;
	void init(json& j) override;

	virtual Entity* spawnEntity(Vector3 pos = Vector3(0, 0, 0), float speed = 0.0,std::string prefab = "");
private:
	std::string defaultPrefab;
	int maxSpawnTime = 120;
	int minSpawnTime = 30;
	int timeToSpawn = 0;
	int timeSinceLastSpawn = 0;
};
