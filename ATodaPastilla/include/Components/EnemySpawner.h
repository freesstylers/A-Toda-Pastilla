#pragma once
#include "EntitySpawner.h"
#include <map>
class EnemySpawner : public EntitySpawner
{
public:
	EnemySpawner(json& args);
	~EnemySpawner() {};
	void init(json& j) override;
	void start() override;
	void update() override;
	void setPosUsed(int indx, bool value);
private:
	float spawnRate;
	float timeSinceSpawn;
	std::vector<std::string> enemies;
	std::vector<Vector3> spawnPositions;
	std::vector<bool> posUsed;
};

