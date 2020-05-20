#include "Components\HermenegildoBehaviour.h"
#include "Entity/Entity.h"
#include "Components/ProjectileSpawner.h"
#include "Audio/AudioManager.h"
#include "Components/VidaEnemigos.h"
#include "Components/ProjectileBehaviour.h"
#include "MotorCasaPaco.h"

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
	if (!j["timeBetweenAttacks"].is_null()) {
		timeBetweenAttacks = j["timeBetweenAttacks"];
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
}

void HermenegildoBehaviour::start()
{
	prSpawner = e_->getComponent<ProjectileSpawner>("ProjectileSpawner");

	shotsFired = 0;
	timeSinceLastAttack = timeBetweenAttacks;
	timeSinceLastShot = cadence;
	dyingTime = 0;
}

void HermenegildoBehaviour::update()
{
	if (!e_->getComponent<VidaEnemigos>("VidaEnemigos")->isDead()) {
		if (prSpawner != nullptr) {
			if (timeSinceLastAttack >= timeBetweenAttacks) {
				if (shotsFired < shotsPerAttack) {
					if (timeSinceLastShot >= cadence) {
						prSpawner->spawnProjectiles(Vector3(-20, 0, 15), Vector3(0, 0, 1), 100, 1, 10);

						prSpawner->spawnProjectiles(Vector3(20, 0, 15), Vector3(0, 0, 1), 100, 1, 10);

						shotsFired++;
						timeSinceLastShot = 0;
					}
					timeSinceLastShot += MotorCasaPaco::getInstance()->DeltaTime();
				}
				else {
					timeSinceLastAttack = 0;
					shotsFired = 0;
				}
			}
			else {
				timeSinceLastAttack += MotorCasaPaco::getInstance()->DeltaTime();
			}
		}
	}
	else {
		dyingTime += MotorCasaPaco::getInstance()->DeltaTime();
		if (dyingTime >= timeToDie) {
			EventManager::getInstance()->UnregisterListenerForAll(e_);
			e_->setEnabled(false);
		}
	}
}

void HermenegildoBehaviour::OnCollision(Entity* other)
{
	if (other->getTag() == "Projectile" && other->getComponent<ProjectileBehaviour>("ProjectileBehaviour")->getSource() == "Player") {
			float x = rand() % 100;
			if (x < 95) {
				AudioManager::getInstance()->playMusic(hitSound.c_str(), 4, false);
			}
			else
				AudioManager::getInstance()->playMusic("assets/sound/movie_1.mp3", 4, false);
	}
}
void HermenegildoBehaviour::OnDeath()
{
	EnemyBehaviour::OnDeath();
	AudioManager::getInstance()->playMusic(deathSound.c_str(), 4, false);
	AudioManager::getInstance()->setVolume(0.7, 4);
	dyingTime = 0;
}


