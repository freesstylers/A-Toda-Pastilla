
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
	float sumX = InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTX, true);
	float sumY = InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTY, true);
	//std::cout << "MandoX: " << sumX << " MandoY: " << sumY << "Posicion:(" << position.X << "," << position.Z << ")\n";
	position += Vector3(sumX, 0.0f, sumY); //Hay que multiplicarlo por el deltaTime
	position = insideBounds(position);

	e_->getComponent<Transform>("Transform")->setPosition(position);

}

void MovimientoMando::init(json& j)
{
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
