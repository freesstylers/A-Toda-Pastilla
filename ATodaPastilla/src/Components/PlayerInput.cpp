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
}

void PlayerInput::init(json& j)
{
}
