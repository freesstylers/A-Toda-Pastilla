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

void Vida::update()
{
	if (timeD_) {
		if (MotorCasaPaco::getInstance()->getTimeDifference(time_) /1000.0f >= timeToLive_)
			sumaVida(-vida_);
	}
}

void Vida::init(json& j)
{
	if (!j["vida"].is_null()) vida_ = j["vida"];
	if (!j["time"].is_null()) {
		timeToLive_ = j["time"];
		time_ = MotorCasaPaco::getInstance()->getTime();
		timeD_ = true;
	}
	
}

void Vida::sumaVida(int valor)
{
	vida_ += valor;
	if (vida_ <= 0) {
		EventManager::getInstance()->UnregisterListenerForAll(e_);
		e_->setEnabled(false);
	}
}
