#pragma once
#include "EntitySpawner.h"
class EnemySpawner : public EntitySpawner
{
public:
	EnemySpawner(json& args);
	~EnemySpawner() {};
	void init(json& j) override;
	void start() override;
	void update() override;
private:
	float spawnRate;
	float timeSinceSpawn;
	std::string riciberga;
	std::string hermenegildo;
	float riciRate;
	float hermRate;
	Vector3 spawnPos;
};

