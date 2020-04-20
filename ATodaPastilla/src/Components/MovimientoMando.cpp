
#include "Components/MovimientoMando.h"
#include "Input/InputManager.h"
#include <iostream>
#include "Entity/Entity.h"
#include "Entity/Transform.h"

MovimientoMando::MovimientoMando(json& args) : Component(args)
{


}

MovimientoMando::~MovimientoMando()
{
	Component::~Component();

}

void MovimientoMando::update()
{
	Vector3 position = e_->getComponent<Transform>("Transform")->getPosition();
	float sumX = InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTX, false);
	float sumY = InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTY, false);

	position += Vector3(sumX, 0.0f, sumY); //Hay que multiplicarlo por el deltaTime
	position = insideBounds(position);

	e_->getComponent<Transform>("Transform")->setPosition(position);

}

void MovimientoMando::init(json& j)
{
	if (!j["xRIGHT"].is_null()) xRIGHT_ = j["xRIGHT"];
	if (!j["xLEFT"].is_null()) xLEFT_ = j["xLEFT"];
	if (!j["yUP"].is_null()) yUP_ = j["yUP"];
	if (!j["yDOWN"].is_null()) yDOWN_ = j["yDOWN"];
}

Vector3 MovimientoMando::insideBounds(Vector3 position)
{
	if (xRIGHT_ < position.X) position.X = xRIGHT_;
	if (xLEFT_ > position.X) position.X = xLEFT_;
	if (yUP_ < position.Z) position.Z = yUP_;
	if (yDOWN_ > position.Z) position.Z = yDOWN_;
	return position;
}
