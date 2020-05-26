#pragma once
#include "EntitySpawner.h"
#include <map>
struct EnemySpawnInfo {
	std::string enemyPrefab;
	std::vector<float> spawnProb;
};
class EnemySpawner : public EntitySpawner
{
public:
	EnemySpawner(json& args);
	~EnemySpawner() {};
	void init(json& j) override;
	void start() override;
	void update() override;
	void setPosUsed(int indx, bool value);
	void spawn();
	int getCurrWave() { return currWave; };
	virtual bool ReceiveEvent(Event& event) override;
private:
	bool lastWave = false;
	float timeSinceSpawn;
	float timeSinceStart;
	float timeSinceMult;
	int currWave;
	int nWaves;
	std::vector<float> waveStart;
	std::vector<int> maxSpawns;
	std::vector<float> spawnRate;
	float multRate;
	float currMult;
	float statMult;
	std::vector<EnemySpawnInfo> enemies;
	std::vector<Vector3> spawnPositions;
	std::vector<bool> posUsed;
};

