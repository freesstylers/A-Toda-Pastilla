#include "Components/EnemySpawner.h"
#include "MotorCasaPaco.h"

EnemySpawner::EnemySpawner(json& args):EntitySpawner(args)
{

}

void EnemySpawner::init(json& j)
{
	EntitySpawner::init(j);
	if (!j["spawnRate"].is_null()) {
		spawnRate = j["spawnRate"];
	}
	if (!j["riciRate"].is_null()) {
		riciRate = j["riciRate"];
	}
	if (!j["hermRate"].is_null()) {
		hermRate = j["hermRate"];
	}
	if (!j["spawnPos"].is_null()&&j["spawnPos"].is_array()) {
		spawnPos.X = j["spawnPos"][0];
		spawnPos.Y = j["spawnPos"][1];
		spawnPos.Z = j["spawnPos"][2];
	}
	if (!j["riciberga"].is_null()) {
		std::string inter = j["riciberga"];
		riciberga = inter;
	}
	if (!j["hermenegildo"].is_null()) {
		std::string inter = j["hermenegildo"];
		hermenegildo = inter;
	}
	
}

void EnemySpawner::start()
{
	timeSinceSpawn = 0;
}

void EnemySpawner::update()
{
	if (timeSinceSpawn >= spawnRate) {
		spawnEntity(spawnPos, riciberga);
		timeSinceSpawn = 0;
	}
	timeSinceSpawn += MotorCasaPaco::getInstance()->DeltaTime();
}
