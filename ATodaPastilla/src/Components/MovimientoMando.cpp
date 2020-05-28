
#include "Components/MovimientoMando.h"
#include "Input/InputManager.h"
#include <iostream>
#include "Entity/Entity.h"
#include "Entity/Transform.h"
#include "MotorCasaPaco.h"
#include "Physics/PhysicsManager.h"
#include "checkML.h"

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

	float sumX = InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTX, true);
	float sumY = InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTY, true);
	float deltaTime = MotorCasaPaco::getInstance()->DeltaTime();

	position += (Vector3(sumX, 0.0f, sumY)* deltaTime *speed_);
	position = insideBounds(position);

	e_->getComponent<Transform>("Transform")->setPosition(position);
	e_->getComponent<Transform>("Transform")->setRotation(Vector3(0.0, 180.0, sumX*30));

}

void MovimientoMando::init(json& j)
{
	if (!j["speed"].is_null()) speed_ = j["speed"];
	if (!j["xRIGHT"].is_null()) xRIGHT_ = j["xRIGHT"];
	if (!j["xLEFT"].is_null()) xLEFT_ = j["xLEFT"];
	if (!j["zUP"].is_null()) zUP_ = j["zUP"];
	if (!j["zDOWN"].is_null()) zDOWN_ = j["zDOWN"]; 
}

Vector3 MovimientoMando::insideBounds(Vector3 position)
{
	if (xRIGHT_ < position.X) position.X = xRIGHT_;
	if (xLEFT_ > position.X) position.X = xLEFT_;
	if (zUP_ > position.Z) position.Z = zUP_;
	if (zDOWN_ < position.Z) position.Z = zDOWN_;
	return position;
}
