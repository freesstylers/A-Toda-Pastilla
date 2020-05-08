#include "Components/RicibergaBehaviour.h"
#include "Components/Vida.h"
#include "Entity/Entity.h"
#include "Audio/AudioManager.h"
#include "Entity/Transform.h"
#include "MotorCasaPaco.h"
#include "Scene/SceneManager.h"
#include "Events/EventManager.h"
#include "Events/Event.h"
#include "Events/EventListener.h"
#include <list>

RicibergaBehaviour::RicibergaBehaviour(json& j): Component(j)
{
}

void RicibergaBehaviour::init(json& j)
{
	Component::init(j);
	seeksPlayer = false;
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
	else if (!j["direction"].is_null() && j["direction"].is_array()) {
		dir.X = j["direction"][0];
		dir.Y = j["direction"][1];
		dir.Z = j["direction"][2];
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
	dying = false;
	if (seeksPlayer) {
		std::list<Entity*> ent = MotorCasaPaco::getInstance()->getSceneManager()->getCurrentScene()->getEntitiesByTag("Player");
		auto p = ent.begin();
		player = (*p);
	}
}

void RicibergaBehaviour::update()
{
	if (!dying) {
		Vector3 pos = getEntity()->getComponent<Transform>("Transform")->getPosition();
		Vector3 playerPos = player->getComponent<Transform>("Transform")->getPosition();
		Vector3 direction;
		if (player != nullptr) {
			direction = playerPos - pos;
			direction = Vector3::Normalized(direction);
		}
		else {
			direction = dir;
		}
		double orientation=Vector3::Angle(Vector3(0, 0, 1), direction);
		orientation = orientation * 180.0 / M_PI;
		if (direction.X < 0) orientation = -orientation;
		getEntity()->getComponent<Transform>("Transform")->setRotation(Vector3(0, orientation, 0));
		getEntity()->getComponent<Transform>("Transform")->setPosition(getEntity()->getComponent<Transform>("Transform")->getPosition() + direction * speed * MotorCasaPaco::getInstance()->DeltaTime());
		if (getEntity()->getComponent<Transform>("Transform")->getPosition().Z >= bottom) dying = true;
	}
	else {
		dyingTime += MotorCasaPaco::getInstance()->DeltaTime();
		if (dyingTime>=timeToDie) {
			EventManager::getInstance()->UnregisterListenerForAll(e_);
			e_->setEnabled(false);
		}
	}
}

void RicibergaBehaviour::OnCollision(Entity* other)
{
	if (!dying) {
		if (other->getTag() == "Player") {
			if (other->getComponent<Vida>("Vida") != nullptr) {
				other->getComponent<Vida>("Vida")->sumaVida(-damage);
			}
		}
		else if (other->getTag() == "Projectile") {
			float x = rand() % 100;
			if (x < 95) {
				MotorCasaPaco::getInstance()->getAudioManager()->playMusic(hitSound.c_str(), 4);
			}
			else
				MotorCasaPaco::getInstance()->getAudioManager()->playMusic("assets/sound/movie_1.mp3", 4);
		}
	}
}

bool RicibergaBehaviour::ReceiveEvent(Event& event)
{
	if (event.type == "DEATH") {
		dying = true;
		MotorCasaPaco::getInstance()->getAudioManager()->playMusic(deathSound.c_str(), 3);
		AudioManager::getInstance()->setVolume(0.7, 3);
		dyingTime = 0;
		return true;
	}
	
	return false;
}