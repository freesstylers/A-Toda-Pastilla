
#include "Entity/Entity.h"
#include "Events/Event.h"
#include "Scene/SceneManager.h"
#include "MotorCasaPaco.h"
#include <iostream>
#include "Components/SpawnerMejora.h"

#include "Components/ProjectileBehaviour.h"

SpawnerMejora::SpawnerMejora(json& args):EntitySpawner(args)
{
	
}

SpawnerMejora::~SpawnerMejora()
{
	Component::~Component();
}

void SpawnerMejora::update()
{
	spawnEntity();
}

void SpawnerMejora::init(json& j)
{
	EntitySpawner::init(j);
	spawnEntity();
}

Entity* SpawnerMejora::spawnEntity(Vector3 pos, Vector3 dir, float speed,std::string prefab)
{
	float iniAngle = 0;

	Entity* prj = EntitySpawner::spawnEntity(pos, prefab);


	prj->getComponent<ProjectileBehaviour>("ProjectileBehaviour")->setDir(dir);
	prj->getComponent<ProjectileBehaviour>("ProjectileBehaviour")->setSpeed(speed);
	std::cout << "spawned" << std::endl;
	return nullptr;
}
