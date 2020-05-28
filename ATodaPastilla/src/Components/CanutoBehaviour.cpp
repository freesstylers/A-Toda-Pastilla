#include "Components\CanutoBehaviour.h"
#include "Entity/Entity.h"
#include "Components/ProjectileSpawner.h"
#include "Audio/AudioManager.h"
#include "Components/VidaEnemigos.h"
#include "Components/ProjectileBehaviour.h"
#include "MotorCasaPaco.h"
#include "Scene/SceneManager.h"
#include "Entity/Entity.h"
#include "Entity/Transform.h"
#include "Components/EnemySpawner.h"
#include "checkML.h"

CanutoBehaviour::CanutoBehaviour(json& args) :EnemyBehaviour(args)
{

}

void CanutoBehaviour::init(json& j)
{
	deathSound = "";
	hitSound = "";
	if (!j["bottom"].is_null()) {
		bottom = j["bottom"];
	}
	if (!j["bulletSpeed"].is_null()) {
		bulletSpeed = j["bulletSpeed"];
	}
	if (!j["minTimeBtwAtk"].is_null()) {
		minTimeBtwAtk = j["minTimeBtwAtk"];
	}
	if (!j["maxTimeBtwAtk"].is_null()) {
		maxTimeBtwAtk = j["maxTimeBtwAtk"];
	}
	if (!j["deathSound"].is_null()) {
		std::string inter = j["deathSound"];
		deathSound = inter;
	}
	if (!j["hitSound"].is_null()) {
		std::string inter = j["hitSound"];
		hitSound = inter;
	}
	if (!j["timeToDie"].is_null()) {
		timeToDie = j["timeToDie"];
	}
	if (!j["damage"].is_null()) {
		damage = j["damage"];
	}
	if (!j["speed"].is_null()) {
		speed = j["speed"];
	}
}

void CanutoBehaviour::start()
{
	prSpawner = e_->getComponent<ProjectileSpawner>("ProjectileSpawner");

	dyingTime = 0;
	damage = 1;
	float x = (rand() % 101) / 100.0;
	timeBetweenAttacks = minTimeBtwAtk + (maxTimeBtwAtk - minTimeBtwAtk) * x;
	timeSinceLastAttack = timeBetweenAttacks * 0.9;
	awayFromSpawn = false;
}

void CanutoBehaviour::update()
{
	if (!e_->getComponent<VidaEnemigos>("VidaEnemigos")->isDead()) {
		if (prSpawner != nullptr) {
			if (timeSinceLastAttack >= timeBetweenAttacks / statMult) {
				prSpawner->spawnProjectiles(Vector3(0, 0, 25), Vector3(0, 0, 1), bulletSpeed * statMult, 1, damage);
				float x = (rand() % 101) / 100.0;
				timeBetweenAttacks = minTimeBtwAtk + (maxTimeBtwAtk - minTimeBtwAtk) * x;
				timeSinceLastAttack = 0;
			}
			timeSinceLastAttack += MotorCasaPaco::getInstance()->DeltaTime();
			
		}
		Vector3 direction;
		Vector3 position = getEntity()->getComponent<Transform>("Transform")->getPosition();
		direction = Vector3(0, 0, 1);
		e_->getComponent<Transform>("Transform")->setPosition(e_->getComponent<Transform>("Transform")->getPosition() + direction * speed * statMult * MotorCasaPaco::getInstance()->DeltaTime());
		
		if(Vector3::Magnitude((e_->getComponent<Transform>("Transform")->getPosition() - spawnPosition)) >= 80) {
			if (!awayFromSpawn) {
				EnemyBehaviour::OnDeath();
				awayFromSpawn = true;
			}
		}
		else {
			std::list<Entity*> l = MotorCasaPaco::getInstance()->getSceneManager()->getCurrentScene()->getEntitiesByTag("EnemySpawner");
			if (!l.empty()) {
				Entity* spawner = (*l.begin());
				if (spawner != nullptr && spawner->getComponent<EnemySpawner>("EnemySpawner") != nullptr) {
					spawner->getComponent<EnemySpawner>("EnemySpawner")->setPosUsed(spawnIndx, true);
				}
			}
		}
		if (position.Z >= bottom) {
			EventManager::getInstance()->UnregisterListenerForAll(e_);
			MotorCasaPaco::getInstance()->getSceneManager()->getCurrentScene()->deleteEntity(e_->getName());
		}
	}
	else {
		dyingTime += MotorCasaPaco::getInstance()->DeltaTime();
		if (dyingTime >= timeToDie) {
			EnemyBehaviour::OnDeath();
			EventManager::getInstance()->UnregisterListenerForAll(e_);
			MotorCasaPaco::getInstance()->getSceneManager()->getCurrentScene()->deleteEntity(e_->getName());
		}
	}
}

void CanutoBehaviour::OnCollision(Entity* other)
{
	if (!e_->getComponent<VidaEnemigos>("VidaEnemigos")->isDead()) {
		if (other->getTag() == "Projectile" && other->getComponent<ProjectileBehaviour>("ProjectileBehaviour")->getSource() == "Player") {
			AudioManager::getInstance()->playMusic(hitSound.c_str(), 4, false);
		}
	}
	if (other->getComponent<EnemyBehaviour>("CanutoBehaviour") != nullptr) {
		other->getComponent<EnemyBehaviour>("CanutoBehaviour")->OnDeath();
		EventManager::getInstance()->UnregisterListenerForAll(other);
		MotorCasaPaco::getInstance()->getSceneManager()->getCurrentScene()->deleteEntity(other->getName());
	}
	else if (other->getComponent<EnemyBehaviour>("HermenegildoBehaviour") != nullptr) {
		other->getComponent<EnemyBehaviour>("HermenegildoBehaviour")->OnDeath();
		EventManager::getInstance()->UnregisterListenerForAll(other);
		MotorCasaPaco::getInstance()->getSceneManager()->getCurrentScene()->deleteEntity(other->getName());
	}
}

void CanutoBehaviour::OnDeath()
{
	AudioManager::getInstance()->playMusic(deathSound.c_str(), 4, false);
	AudioManager::getInstance()->setVolume(0.7, 4);
	dyingTime = 0;
}
