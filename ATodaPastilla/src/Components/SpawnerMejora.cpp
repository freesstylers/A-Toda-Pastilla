
#include "Entity/Entity.h"
#include "Events/Event.h"
#include "Scene/SceneManager.h"
#include "MotorCasaPaco.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Components/SpawnerMejora.h"

#include "Entity/Transform.h"

SpawnerMejora::SpawnerMejora(json& args):EntitySpawner(args)
{
	
}

SpawnerMejora::~SpawnerMejora()
{
	Component::~Component();
}

void SpawnerMejora::update()
{
	if (timeSinceLastSpawn >= timeToSpawn) {
		randomMejora = (rand() % 3);
		switch (randomMejora)
		{
		case 0:
			spawnEntity(Vector3(150, e_->getComponent<Transform>("Transform")->getPosition().Y, -250), 0.0, "MejoraDisparo");
			break;
		case 1:
			spawnEntity(Vector3(-150, e_->getComponent<Transform>("Transform")->getPosition().Y, -250), 0.0, "MejoraVida");
			break;
		case 2:
			spawnEntity(Vector3(-0, e_->getComponent<Transform>("Transform")->getPosition().Y, -250), 0.0, "MejoraEutanasia");
			break;
		default:
			std::cout << "Nunca deber�a salir este mensaje" << std::endl;
			break;
		}
		timeToSpawn = (rand() % (int)(maxSpawnTime)) + minSpawnTime;
		timeSinceLastSpawn = 0;
	}
	timeSinceLastSpawn += MotorCasaPaco::getInstance()->DeltaTime();

}

void SpawnerMejora::init(json& j)
{
	srand((unsigned)time(NULL));
	EntitySpawner::init(j);
	timeToSpawn = 5;

}

Entity* SpawnerMejora::spawnEntity(Vector3 pos, float speed,std::string prefab)
{
	std::cout << "spawned" << std::endl;

	Entity* prj = EntitySpawner::spawnEntity(pos, prefab);

	prj->getComponent<Transform>("Transform")->setRotation(Vector3(0, -95, 90));
	return prj;
}
