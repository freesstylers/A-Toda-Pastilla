#include "Components/RicibergaBehaviour.h"
#include "Components/Vida.h"
#include "Entity/Entity.h"
#include "Audio/AudioManager.h"
#include "Entity/Transform.h"
#include "MotorCasaPaco.h"
#include "Scene/SceneManager.h"
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
	if (!j["seeksPlayer"].is_null()) {
		seeksPlayer = j["seeksPlayer"];
	}
	else if (!j["direction"].is_null() && j["direction"].is_array()) {
		dir.X = j["direction"][0];
		dir.Y = j["direction"][1];
		dir.Z = j["direction"][2];
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
		MotorCasaPaco::getInstance()->getAudioManager()->playMusic("assets/sound/shotSound.mp3", 3);
		getEntity()->getComponent<Vida>("Vida")->sumaVida(-100);
	}
}

void RicibergaBehaviour::OnCollision(Entity* other)
{
	if (other->getTag() == "Player" && !dying) {
		if (other->getComponent<Vida>("Vida") != nullptr) {
			other->getComponent<Vida>("Vida")->sumaVida(-damage);
			dying = true;
		}
	}
	else if (other->getTag() == "Projectile" && !dying) {
		float x=rand() % 100;
		if (x < 90) {
			MotorCasaPaco::getInstance()->getAudioManager()->playMusic("assets/sound/hit1.mp3", 4);
		}
		else
			MotorCasaPaco::getInstance()->getAudioManager()->playMusic("assets/sound/movie_1.mp3", 4);
	}
}