#include "Components\Vida.h"
#include "Entity/Entity.h"
#include "Events/Event.h"
#include "Scene/SceneManager.h"
#include "MotorCasaPaco.h"
#include <iostream>

Vida::Vida(json& args): Component(args)
{
}

Vida::~Vida()
{
	Component::~Component();
}

void Vida::start()
{
	vida_ = vidaMax_;
	death_ = false;
}

void Vida::update()
{
	if (timeD_) {
		time_ += MotorCasaPaco::getInstance()->DeltaTime();
		if (time_ >= timeToLive_)
			sumaVida(-vida_);
	}
}

void Vida::init(json& j)
{
	if (!j["vidaMax"].is_null()) 
		vidaMax_ = j["vidaMax"];
	if (!j["time"].is_null()) {
		timeToLive_ = j["time"];
		timeD_ = true;
	}
	if (!j["customDeath"].is_null() && j["customDeath"]) {
		customDeath_ = true;
	}
	else customDeath_ = false;
	
}

void Vida::sumaVida(int valor)
{
	vida_ += valor;
	if (vida_ >= vidaMax_)
		vida_ = vidaMax_;
	else if (vida_ <= 0 && !death_) {
		if (!customDeath_) {
			EventManager::getInstance()->UnregisterListenerForAll(e_);
			MotorCasaPaco::getInstance()->getSceneManager()->getCurrentScene()->deleteEntity(e_->getName());
		}
		else {
			EventManager::getInstance()->UnregisterListenerForAll(e_);
			EventManager::getInstance()->RegisterListener(e_, "DEATH");
			EventManager::getInstance()->EmitEvent("DEATH");
			EventManager::getInstance()->UnregisterListenerForAll(e_);
		}
		death_ = true;
	}
}
