#include "Components/PlayerInput.h"
#include "Input/InputManager.h"
#include "Components/GameManager.h"

PlayerInput::PlayerInput(json& args) : Component(args)
{
}

PlayerInput::~PlayerInput()
{
}

void PlayerInput::alwaysLateUpdate()
{
	if (InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_START)
		|| InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_ESCAPE)) {
		if (!pausePressed_) {
			pausePressed_ = true;
			GameManager::getInstance()->pause();
		}
	}
	else
		pausePressed_ = false;
}

void PlayerInput::init(json& j)
{
}
