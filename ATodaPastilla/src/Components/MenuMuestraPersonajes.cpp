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
}

void MenuMuestraPersonaje::nextCharacter()
{
	SceneManager::getInstance()->getCurrentScene()->getEntity(entidades_[n_])->setActive(false);
	n_++;
	n_ = n_ % 4;
	spawnEntity(pos_, entidades_[n_]);
}

void MenuMuestraPersonaje::prevCharacter()
{
	SceneManager::getInstance()->getCurrentScene()->getEntity(entidades_[n_])->setActive(false);
	if (n_ != 0)n_--; else n_ = 3;
	spawnEntity(pos_, entidades_[n_]);
}
