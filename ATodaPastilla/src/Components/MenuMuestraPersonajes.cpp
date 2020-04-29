#include "Components/MenuMuestraPersonaje.h"
#include "Scene/SceneManager.h"
#include "MotorCasaPaco.h"
#include "Input/InputManager.h"
#include "Entity/Transform.h"

MenuMuestraPersonaje::MenuMuestraPersonaje(json& args) : EntitySpawner(args)
{

}

MenuMuestraPersonaje::~MenuMuestraPersonaje()
{

}

void MenuMuestraPersonaje::update()
{
	//nextCharacter();
}

void MenuMuestraPersonaje::nextCharacter()
{
	SceneManager::getInstance()->getCurrentScene()->deleteEntity(entidades_[n_]);
	n_++;
	n_ = n_ % 4;
	spawnEntity(pos_, entidades_[n_]);
}

void MenuMuestraPersonaje::prevCharacter()
{
	SceneManager::getInstance()->getCurrentScene()->deleteEntity(entidades_[n_]);
	if (n_ != 0)n_--; else n_ = 3;
	spawnEntity(pos_, entidades_[n_]);
}

bool MenuMuestraPersonaje::function1(const CEGUI::EventArgs& e)
{
	prevCharacter();
	return true;
}

bool MenuMuestraPersonaje::function2(const CEGUI::EventArgs& e)
{
	nextCharacter();
	return true;
}

void MenuMuestraPersonaje::init(json& j)
{
	if (!j["position"].is_null()) {
		pos_.X = j["position"][0];
		pos_.Y = j["position"][1];
		pos_.Z = j["position"][2];
	}
	if (!j["entidades"].is_null()) {
		entidades_.push_back(j["entidades"][0]);
		entidades_.push_back(j["entidades"][1]);
		entidades_.push_back(j["entidades"][2]);
		entidades_.push_back(j["entidades"][3]);
	}
	spawnEntity(pos_, entidades_[0]);

	if (!j["buttonName1"].is_null() && !j["buttonName2"].is_null())
	{
		auto helperFunction1 = std::bind(&MenuMuestraPersonaje::function1, this, std::placeholders::_1);
		auto helperFunction2 = std::bind(&MenuMuestraPersonaje::function2, this, std::placeholders::_1);
		GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(j["buttonName1"]), helperFunction1);
		GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(j["buttonName2"]), helperFunction2);
	}
}
