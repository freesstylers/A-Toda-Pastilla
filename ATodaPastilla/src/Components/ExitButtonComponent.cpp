#include "Components/ExitButtonComponent.h"
#include "MotorCasaPaco.h"
#include "Audio/AudioManager.h"
#include "checkML.h"

ExitButtonComponent::ExitButtonComponent(json& args): Component(args)
{

}

ExitButtonComponent::~ExitButtonComponent()
{
	Component::~Component();
}

bool ExitButtonComponent::function(const CEGUI::EventArgs& e)
{
	AudioManager::getInstance()->playMusic("assets/sound/buttonSound.mp3", 2, false);
	MotorCasaPaco::getInstance()->exit();
	return true;
}

void ExitButtonComponent::init(json& j)
{
	if (!j["buttonName"].is_null())
	{
		auto helperFunction = std::bind(&ExitButtonComponent::function, this, std::placeholders::_1);
		GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(j["buttonName"]), helperFunction);
	}
}
