#include "Components\EnemyBehaviour.h"
#include "Components/EnemySpawner.h"
#include "MotorCasaPaco.h"
#include "Scene/SceneManager.h"
#include "checkML.h"


EnemyBehaviour::EnemyBehaviour(json& args):Component(args)
{

}

void EnemyBehaviour::setSpawnPos(Vector3 spawnPos)
{
	spawnPosition = spawnPos;
}

void EnemyBehaviour::setEnemyIndx(int indx)
{
	spawnIndx = indx;
}

void EnemyBehaviour::setStatMult(float mult)
{
	statMult = mult;
}

void EnemyBehaviour::start()
{
	statMult = 1;
}

void EnemyBehaviour::OnDeath()
{
	std::list<Entity*> l=MotorCasaPaco::getInstance()->getSceneManager()->getCurrentScene()->getEntitiesByTag("EnemySpawner");
	if (!l.empty()) {
		Entity* spawner = (*l.begin());
		if (spawner != nullptr && spawner->getComponent<EnemySpawner>("EnemySpawner")!=nullptr) {
			spawner->getComponent<EnemySpawner>("EnemySpawner")->setPosUsed(spawnIndx, false);
		}
	}
}

bool EnemyBehaviour::ReceiveEvent(Event& event)
{
	if (event.type == "DEATH") {
		OnDeath();
		return true;
	}

	return false;
}
