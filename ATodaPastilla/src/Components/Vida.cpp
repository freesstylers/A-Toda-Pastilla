#include "Components\Vida.h"
#include "Entity/Entity.h"
#include "Events/Event.h"
#include "Scene/SceneManager.h"
#include "MotorCasaPaco.h"
#include <iostream>

Vida::Vida(json& args): Component(args)
{
	EventManager::getInstance()->RegisterListener(getEntity(), "DEATH");
}

Vida::~Vida()
{
	Component::~Component();
}

void Vida::start()
{
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
	if (!j["vida"].is_null()) vida_ = j["vida"];
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
	if (vida_ <= 0&& !death_) {
		if (!customDeath_) {
			EventManager::getInstance()->UnregisterListenerForAll(e_);
			e_->setEnabled(false);
		}
		else
			EventManager::getInstance()->EmitEvent("DEATH");

		death_ = true;
	}
}
