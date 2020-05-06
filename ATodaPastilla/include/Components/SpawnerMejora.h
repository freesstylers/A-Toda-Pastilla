#pragma once


#include "Entity\Component.h"
#include "EntitySpawner.h"

class SpawnerMejora : public EntitySpawner
{
public:
	SpawnerMejora(json& args);
	~SpawnerMejora();
	virtual void update() override;
	virtual void init(json& j) override;

	virtual Entity* spawnEntity(Vector3 pos = Vector3(0, 0, 0), Vector3 dir = Vector3(0, -1, 0), float speed = 0.0,std::string prefab = "");
private:
	std::string defaultPrefab;

};
