#include "Components/PlayerInput.h"
#include "Input/InputManager.h"

PlayerInput::PlayerInput(json& args) : Component(args)
{
}

PlayerInput::~PlayerInput()
{
}

void PlayerInput::update()
{
	if (InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_START)) {
		if (!pausePressed_) {
			pausePressed_ = true;
			EventManager::getInstance()->EmitEvent("PAUSE");
		}
	}
	else
		pausePressed_ = false;
}

void PlayerInput::init(json& j)
{
}
