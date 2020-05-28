#include "Components/CameraBehavior.h"
#include "Components/EventsGame.h"
#include "Entity/Entity.h"
#include "Entity/Transform.h"
#include "MotorCasaPaco.h"

CameraBehavior::CameraBehavior(json& args): Component(args)
{

}

CameraBehavior::~CameraBehavior()
{

}

void CameraBehavior::init(json& j)
{
	if (!j["time"].is_null()) {
		t_ = j["time"];
	}
	if (!j["intensity"].is_null() && j["intensity"].is_array()) {
		for (int i = 0; i < j["intensity"].size(); i++) {
			x_.push_back(j["intensity"][i]);
		}
		//x_ = j["intensity"];
	}

	//EventManager::getInstance()->RegisterListener(e_, "EnemyDeath");
	EventManager::getInstance()->RegisterListener(e_, "Hit");
	EventManager::getInstance()->RegisterListener(e_, "MejoraDisparo1");
	EventManager::getInstance()->RegisterListener(e_, "MejoraDisparo2");

	iniX_ = e_->getTransform()->getPosition().X;
	iniZ_ = e_->getTransform()->getPosition().Z;
}

void CameraBehavior::update()
{
	if (start_) {
		ticks += MotorCasaPaco::getInstance()->DeltaTime();
		vibrar();
	}
}

bool CameraBehavior::ReceiveEvent(Event& event)
{
	/*if (event.type == "EnemyDeath") {
		start_ = true;
	} else*/ if (event.type == "Hit") {
		start_ = true;
	}
	else if (event.type == "MejoraDisparo1") {
		n = 1;
	}
	else if (event.type == "MejoraDisparo2") {
		n = 2;
	}

	return false;
}

void CameraBehavior::vibrar()
{
	float aux;
	float aux1;
	if (ticks < t_/4.0) {
		aux = (x_[n] * ticks) / (t_ / 4.0);
		e_->getTransform()->setPosition(Vector3(iniX_+aux, e_->getTransform()->getPosition().Y, iniZ_));
	}
	else if (ticks < t_ / 2.0) {
		aux = x_[n] - (x_[n] * ticks) / (t_ / 2.0);
		aux1 = (-x_[n] * ticks) / (t_ / 4.0);
		e_->getTransform()->setPosition(Vector3(aux+iniX_, e_->getTransform()->getPosition().Y, aux1+iniZ_));
	}
	else if (ticks < 3.0*t_ / 4.0) {
		aux = (-x_[n] * ticks) / (t_ / 4.0);
		aux1 = x_[n] - (x_[n] * ticks) / (t_ / 2.0);
		e_->getTransform()->setPosition(Vector3(aux+iniX_, e_->getTransform()->getPosition().Y, aux1+iniZ_));
	}
	else if (ticks < t_ ) {
		aux = -x_[n] + (x_[n] * ticks) / (t_ / 4.0);
		e_->getTransform()->setPosition(Vector3(aux+iniX_, e_->getTransform()->getPosition().Y, aux+iniZ_));
	}
	else {
		e_->getTransform()->setPosition(Vector3(iniX_, e_->getTransform()->getPosition().Y, iniZ_));
		ticks = 0;
		start_ = false;
	}
}