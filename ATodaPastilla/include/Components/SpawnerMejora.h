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
	float maxSpawnTime = 40;
	float minSpawnTime = 5;
	float timeToSpawn = 0;
	float timeSinceLastSpawn = 0;
};
