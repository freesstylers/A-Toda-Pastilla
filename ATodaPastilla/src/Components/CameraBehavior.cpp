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
	if (!j["intensity"].is_null()) {
		x_ = j["intensity"];
	}

	EventManager::getInstance()->RegisterListener(e_, "EnemyDeath");
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
	if (event.type == "EnemyDeath") {
		//e_->getTransform()->setPosition(Vector3(400, e_->getTransform()->getPosition().Y, 0.0));
		start_ = true;
	}

	return false;
}

void CameraBehavior::vibrar()
{
	float aux;
	//Parece que no hay vibracion
	if (ticks < t_/4.0) {
		aux = (x_ * ticks) / (t_ / 4.0);
		e_->getTransform()->setPosition(Vector3(aux, e_->getTransform()->getPosition().Y, 0.0));
	}
	else if (ticks < t_ / 2.0) {
		aux = x_ - (x_ * ticks) / (t_ / 2.0);
		e_->getTransform()->setPosition(Vector3(aux, e_->getTransform()->getPosition().Y, 0.0));
	}
	else if (ticks < 3.0*t_ / 4.0) {
		aux = (-x_ * ticks) / (t_ / 4.0);
		e_->getTransform()->setPosition(Vector3(aux, e_->getTransform()->getPosition().Y, 0.0));
	}
	else if (ticks < t_ ) {
		aux = -x_ + (x_ * ticks) / (t_ / 4.0);
		e_->getTransform()->setPosition(Vector3(aux, e_->getTransform()->getPosition().Y, 0.0));		
	}
	else {
		e_->getTransform()->setPosition(Vector3(iniX_, e_->getTransform()->getPosition().Y, 0.0));
		ticks = 0;
		start_ = false;
	}
	//std::cout << aux << " " << ticks << "\n";
}