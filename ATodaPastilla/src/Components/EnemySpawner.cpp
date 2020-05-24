#include "Components/EnemySpawner.h"
#include "MotorCasaPaco.h"
#include "Components/EnemyBehaviour.h"

EnemySpawner::EnemySpawner(json& args):EntitySpawner(args)
{

}

void EnemySpawner::init(json& j)
{
	EntitySpawner::init(j);
	if (!j["nWaves"].is_null()) {
		nWaves = j["nWaves"];
	}

	if (!j["waveStart"].is_null() && j["waveStart"].is_array()) {
		for (int i = 0; i < j["waveStart"].size(); i++) {
			waveStart.push_back(j["waveStart"][i]);
		}
	}
	if (!j["maxSpawns"].is_null() && j["maxSpawns"].is_array()) {
		for (int i = 0; i < j["maxSpawns"].size(); i++) {
			maxSpawns.push_back(j["maxSpawns"][i]);
		}
	}
	if (!j["spawnRate"].is_null() && j["spawnRate"].is_array()) {
		for (int i = 0; i < j["spawnRate"].size(); i++) {
			spawnRate.push_back(j["spawnRate"][i]);
		}
	}
	if (!j["multRate"].is_null()) {
		multRate = j["multRate"];
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
		std::vector<json> e = j["enemies"];
		for (json c : e) {
			EnemySpawnInfo eSpawn;
			if (!c["enemy"].is_null()) {
				std::string inter = c["enemy"];
				eSpawn.enemyPrefab = inter;
			}
			if (!c["spawnProbability"].is_null() && c["spawnProbability"].is_array()) {
				for(int i=0; i< c["spawnProbability"].size(); i++)
					eSpawn.spawnProb.push_back(c["spawnProbability"][i]);
			}
			else if (!c["spawnProbability"].is_null()) {
				for (int i = 0; i < nWaves; i++) {
					eSpawn.spawnProb.push_back(c["spawnProbability"]);
				}
			}
			enemies.push_back(eSpawn);
		}
	}
	if (!j["statMultiplier"].is_null()) {
		statMult =j["statMultiplier"];
	}
	
}

void EnemySpawner::start()
{
	timeSinceSpawn = 0;
	timeSinceStart = 0;
	timeSinceMult = 0;
	currMult = 1;
	lastWave = false;
	posUsed = std::vector<bool>(spawnPositions.size(), false);
}

void EnemySpawner::update()
{
	
	if (!lastWave) {
		if (timeSinceSpawn >= spawnRate[currWave]) {
			spawn();
		}
		if (timeSinceStart >= waveStart[currWave]) {
			currWave++;
			if (currWave == waveStart.size() - 1) {
				lastWave = true;
			}
			timeSinceSpawn = 0;
		}
	}
	else {
		if (timeSinceSpawn >= spawnRate[currWave]) {
			if (timeSinceMult >= multRate) {
				currMult *= statMult;
				timeSinceMult = 0;
			}
			spawn();
		}
		timeSinceMult += MotorCasaPaco::getInstance()->DeltaTime();
	}
	timeSinceSpawn += MotorCasaPaco::getInstance()->DeltaTime();
	timeSinceStart += MotorCasaPaco::getInstance()->DeltaTime();
	for (int i = 0; i < posUsed.size(); i++) {
		std::cout << posUsed[i] << " ";
	}
	std::cout << "\n";
}


void EnemySpawner::setPosUsed(int indx, bool value)
{
	if(indx<posUsed.size())
		posUsed[indx] = value;
}

void EnemySpawner::spawn()
{
	int s = rand() % spawnPositions.size();
	int i = 0;
	while (i < posUsed.size() && posUsed[s]) {
		s = (s + 1) % posUsed.size();
		i++;
	}
	if (!posUsed[s]) {
		int r = rand() % 100;
		int i = 0;
		float aux = 0;
		while (i < enemies.size()) {
			if (r > aux&& r <= enemies[i].spawnProb[currWave]+aux)
				break;
			aux += enemies[i].spawnProb[currWave];
			i++;
		}
		if (i >= enemies.size()) i=enemies.size()-1;
		Entity* e = spawnEntity(spawnPositions[s], enemies[i].enemyPrefab);
		std::string str = enemies[i].enemyPrefab;
		std::string enemyName = str.substr(0, str.find("_"));
		e->getComponent<EnemyBehaviour>(enemyName + "Behaviour")->setStatMult(currMult);
		e->getComponent<EnemyBehaviour>(enemyName + "Behaviour")->setSpawnPos(spawnPositions[s]);
		e->getComponent<EnemyBehaviour>(enemyName + "Behaviour")->setEnemyIndx(s);
		posUsed[s] = true;
	}
	timeSinceSpawn = 0;

}
