#include "Components\HermenegildoBehaviour.h"
#include "Entity/Entity.h"
#include "Components/ProjectileSpawner.h"
#include "Audio/AudioManager.h"
#include "Components/VidaEnemigos.h"
#include "Components/ProjectileBehaviour.h"
#include "MotorCasaPaco.h"
#include "Scene/SceneManager.h"
#include "Components/EnemySpawner.h"


HermenegildoBehaviour::HermenegildoBehaviour(json& args):EnemyBehaviour(args)
{

}

void HermenegildoBehaviour::init(json& j)
{

	deathSound = "";
	hitSound = "";
	if (!j["cadence"].is_null()) {
		cadence =j["cadence"];
	}
	if (!j["shotsPerAttack"].is_null()) {
		shotsPerAttack = j["shotsPerAttack"];
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

void HermenegildoBehaviour::start()
{
	prSpawner = e_->getComponent<ProjectileSpawner>("ProjectileSpawner");

	shotsFired = 0;
	timeSinceLastShot = cadence;
	dyingTime = 0;
	damage = 1;
	float x = (rand() % 101)/100.0;
	timeBetweenAttacks= minTimeBtwAtk + (maxTimeBtwAtk - minTimeBtwAtk) * x;
	timeSinceLastAttack = timeBetweenAttacks * 0.9;
}

void HermenegildoBehaviour::update()
{
	if (!e_->getComponent<VidaEnemigos>("VidaEnemigos")->isDead()) {
		if (prSpawner != nullptr) {
			if (timeSinceLastAttack >= timeBetweenAttacks/statMult) {
				if (shotsFired < shotsPerAttack) {
					if (timeSinceLastShot >= cadence/statMult) {
						prSpawner->spawnProjectiles(Vector3(-20, 0, 15), Vector3(0, 0, 1), speed*statMult, 1, damage);

						prSpawner->spawnProjectiles(Vector3(20, 0, 15), Vector3(0, 0, 1), speed*statMult, 1, damage);

						shotsFired++;
						timeSinceLastShot = 0;
					}
					timeSinceLastShot += MotorCasaPaco::getInstance()->DeltaTime();
				}
				else {
					timeSinceLastAttack = 0;
					shotsFired = 0;
					float x = (rand() % 101) / 100.0;
					timeBetweenAttacks = minTimeBtwAtk + (maxTimeBtwAtk - minTimeBtwAtk) * x;
				}
			}
			else {
				timeSinceLastAttack += MotorCasaPaco::getInstance()->DeltaTime();
			}
		}
		std::list<Entity*> l = MotorCasaPaco::getInstance()->getSceneManager()->getCurrentScene()->getEntitiesByTag("EnemySpawner");
		if (!l.empty()) {
			Entity* spawner = (*l.begin());
			if (spawner != nullptr && spawner->getComponent<EnemySpawner>("EnemySpawner") != nullptr) {
				spawner->getComponent<EnemySpawner>("EnemySpawner")->setPosUsed(spawnIndx, true);
			}
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

void HermenegildoBehaviour::OnCollision(Entity* other)
{
	if (!e_->getComponent<VidaEnemigos>("VidaEnemigos")->isDead()) {
		if (other->getTag() == "Projectile" && other->getComponent<ProjectileBehaviour>("ProjectileBehaviour")->getSource() == "Player") {
			float x = rand() % 100;
			if (x < 95) {
				AudioManager::getInstance()->playMusic(hitSound.c_str(), 4, false);
			}
			else
				AudioManager::getInstance()->playMusic("assets/sound/HermenegildoDeath.mp3", 4, false);
		}
	}
	if (other->getComponent<HermenegildoBehaviour>("HermenegildoBehaviour") != nullptr) {
		other->getComponent<EnemyBehaviour>("HermenegildoBehaviour")->OnDeath();
		EventManager::getInstance()->UnregisterListenerForAll(other);
		MotorCasaPaco::getInstance()->getSceneManager()->getCurrentScene()->deleteEntity(other->getName());
	}
}
void HermenegildoBehaviour::OnDeath()
{
	AudioManager::getInstance()->playMusic(deathSound.c_str(), 4, false);
	AudioManager::getInstance()->setVolume(0.7, 4);
	dyingTime = 0;
}


