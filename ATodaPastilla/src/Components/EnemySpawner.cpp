#include "Components/EnemySpawner.h"
#include "MotorCasaPaco.h"
#include "Components/EnemyBehaviour.h"

EnemySpawner::EnemySpawner(json& args):EntitySpawner(args)
{

}

void EnemySpawner::init(json& j)
{
	EntitySpawner::init(j);
	if (!j["spawnRate"].is_null()) {
		spawnRate = j["spawnRate"];
	}
	if (!j["spawnPositions"].is_null()&&j["spawnPositions"].is_array()) {
		for (int i = 0; i < j["spawnPositions"].size(); i++) {
			if (j["spawnPositions"][i].is_array()) {
				Vector3 aux;
				aux.X = j["spawnPositions"][i][0];
				aux.Y = j["spawnPositions"][i][1];
				aux.Z = j["spawnPositions"][i][2];
				spawnPositions.push_back(aux);
			}
		}
	}
	if (!j["enemies"].is_null() && j["enemies"].is_array()) {
		for (int i = 0; i < j["enemies"].size(); i++) {
			std::string inter = j["enemies"][i];
			enemies.push_back(inter);
		}
	}
	
}

void EnemySpawner::start()
{
	timeSinceSpawn = 0;
	posUsed = std::vector<bool>(spawnPositions.size(), false);
}

void EnemySpawner::update()
{
	if (timeSinceSpawn >= spawnRate) {
		int s = rand() % spawnPositions.size();
		int i = 0;
		while (i<posUsed.size() && posUsed[s]) {
			s = (s + 1) % posUsed.size();
			i++;
		}
		if (!posUsed[s]) {
			int r = rand() % enemies.size();
			Entity* e = spawnEntity(spawnPositions[s], enemies[r]);
			e->getComponent<EnemyBehaviour>(enemies[r] + "Behaviour")->setSpawnPos(spawnPositions[s]);
			e->getComponent<EnemyBehaviour>(enemies[r] + "Behaviour")->setEnemyIndx(s);
			posUsed[s] = true;
		}
		timeSinceSpawn = 0;
	}
	timeSinceSpawn += MotorCasaPaco::getInstance()->DeltaTime();
	for (int i = 0; i < posUsed.size(); i++) {
		std::cout << i << " " << posUsed[i] << std::endl;
	}
}

void EnemySpawner::setPosUsed(int indx, bool value)
{
	if(indx<posUsed.size())
		posUsed[indx] = value;
}
