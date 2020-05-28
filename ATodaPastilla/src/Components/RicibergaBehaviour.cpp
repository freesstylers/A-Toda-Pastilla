#include "Components/RicibergaBehaviour.h"
#include "Components/VidaEnemigos.h"
#include "Components/VidaPlayer.h"
#include "Entity/Entity.h"
#include "Audio/AudioManager.h"
#include "Entity/Transform.h"
#include "MotorCasaPaco.h"
#include "Components/ProjectileBehaviour.h"
#include "Scene/SceneManager.h"
#include "Events/EventManager.h"
#include "Events/Event.h"
#include "Events/EventListener.h"
#include "Components/EnemySpawner.h"
#include <list>
#include "checkML.h"

RicibergaBehaviour::RicibergaBehaviour(json& j): EnemyBehaviour(j)
{
}

void RicibergaBehaviour::init(json& j)
{
	EnemyBehaviour::init(j);
	seeksPlayer = false;
	sinusoidalMovement = false;
	if (!j["damage"].is_null()) {
		damage = j["damage"];
	}
	if (!j["speed"].is_null()) {
		speed = j["speed"];
	}
	if (!j["bottom"].is_null()) {
		bottom = j["bottom"];
	}
	if (!j["timeToDie"].is_null()) {
		timeToDie = j["timeToDie"];
	}
	if (!j["seeksPlayer"].is_null()) {
		seeksPlayer = j["seeksPlayer"];
	}
	if (!j["sinusoidalMovement"].is_null()) {
		sinusoidalMovement = j["sinusoidalMovement"];
		if (sinusoidalMovement) {
			if (!j["sinusoidalMagnitude"].is_null()) {
				sinusoidalMagnitude = j["sinusoidalMagnitude"];
			}
			if (!j["sinusoidalFrequency"].is_null()) {
				sinusoidalFrequency = j["sinusoidalFrequency"];
			}
		}
	}

	if (!j["hitSound"].is_null()) {
		std::string inter = j["hitSound"];
		hitSound = inter;
	}
	if (!j["deathSound"].is_null()) {
		std::string inter = j["deathSound"];
		deathSound = inter;
	}
}

void RicibergaBehaviour::start()
{
	if (seeksPlayer) {
		std::list<Entity*> ent = MotorCasaPaco::getInstance()->getSceneManager()->getCurrentScene()->getEntitiesByTag("Player");
		auto p = ent.begin();
		player = (*p);
	}
	awayFromSpawn = false;
}

void RicibergaBehaviour::update()
{
	if (e_->getComponent<VidaEnemigos>("VidaEnemigos") != nullptr && !e_->getComponent<VidaEnemigos>("VidaEnemigos")->isDead()) {
		Vector3 pos = getEntity()->getComponent<Transform>("Transform")->getPosition();
		Vector3 direction;
		if (player != nullptr) {
			Vector3 playerPos = player->getComponent<Transform>("Transform")->getPosition();
			direction = playerPos - pos;
		}
		else {
			direction = Vector3(0, 0, 1);
		}

		direction = Vector3::Normalized(direction);
		double orientation=Vector3::Angle(Vector3(0, 0, 1), direction);
		orientation = orientation * 180.0 / M_PI;
		if (direction.X < 0) orientation = -orientation;
		e_->getComponent<Transform>("Transform")->setRotation(Vector3(0, orientation, 0));
		e_->getComponent<Transform>("Transform")->setPosition(e_->getComponent<Transform>("Transform")->getPosition() + direction * speed *statMult* MotorCasaPaco::getInstance()->DeltaTime());
		if (sinusoidalMovement) {
			e_->getComponent<Transform>("Transform")->setPosition(e_->getComponent<Transform>("Transform")->getPosition() + 
				Vector3(sin(MotorCasaPaco::getInstance()->getTime() * sinusoidalFrequency) * sinusoidalMagnitude, 0, 0) * MotorCasaPaco::getInstance()->DeltaTime());
		}
		if (Vector3::Magnitude((e_->getComponent<Transform>("Transform")->getPosition() - spawnPosition)) >= 80) {
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
		if (e_->getComponent<Transform>("Transform")->getPosition().Z >= bottom) {
			EventManager::getInstance()->UnregisterListenerForAll(e_);
			MotorCasaPaco::getInstance()->getSceneManager()->getCurrentScene()->deleteEntity(e_->getName());
		}
	}
	else {
		dyingTime += MotorCasaPaco::getInstance()->DeltaTime();
		if (dyingTime>=timeToDie) {
			EnemyBehaviour::OnDeath();
			EventManager::getInstance()->UnregisterListenerForAll(e_);
			MotorCasaPaco::getInstance()->getSceneManager()->getCurrentScene()->deleteEntity(e_->getName());
		}
	}
}

void RicibergaBehaviour::OnCollision(Entity* other)
{
	if (e_->getComponent<VidaEnemigos>("VidaEnemigos")!=nullptr && !e_->getComponent<VidaEnemigos>("VidaEnemigos")->isDead()) {
		if (other->getTag() == "Player") {
			if (other->getComponent<VidaPlayer>("VidaPlayer") != nullptr) {
				std::cout << "ColisionPlayer" << std::endl;
				other->getComponent<VidaPlayer>("VidaPlayer")->sumaVida(-damage);
				e_->getComponent<VidaEnemigos>("VidaEnemigos")->sumaVida(e_->getComponent<VidaEnemigos>("VidaEnemigos")->GetVida());
			}
		}
		else if (other->getTag() == "Projectile" && other->getComponent<ProjectileBehaviour>("ProjectileBehaviour")->getSource()=="Player") {
			float x = rand() % 100;
			if (x < 95) {
				AudioManager::getInstance()->playMusic(hitSound.c_str(), 4, false);
			}
			else
				AudioManager::getInstance()->playMusic("assets/sound/RicibergaHit.mp3", 4, false);
		}
	}
}

void RicibergaBehaviour::OnDeath()
{
	AudioManager::getInstance()->playMusic(deathSound.c_str(), 3, false);
	AudioManager::getInstance()->setVolume(0.7, 3);
	dyingTime = 0;
}
