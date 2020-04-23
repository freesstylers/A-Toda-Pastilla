#include "Components/EntitySpawner.h"
#include "Entity/Entity.h"
#include "Entity/Transform.h"
#include "MotorCasaPaco.h"
#include "Resources/ResourceManager.h"
#include "Scene/SceneManager.h"
#include "Input/InputManager.h"
#include "Input/PacoKeys.h"
#include <string>

EntitySpawner::EntitySpawner(json& args):Component(args)
{

}

void EntitySpawner::init(json& j)
{
	if (!j["prefab"].is_null()) {
		std::string aux = j["prefab"];
		defaultPrefab = aux;
	}
}

void EntitySpawner::update()
{
	auto i = items.begin();
	while(i!=items.end()){
		auto aux = i;
		aux++;
		if (!((*i).first)->getActive()) {
			delete (*i).first;
			idsUnused.push_back((*i).second);
			items.erase(i);
		}
		i = aux;
	}
	std::cout << items.size()<< "\n";

	if (MotorCasaPaco::getInstance()->getInputManager()->GameControllerIsButtonDown(CONTROLLER_BUTTON_A)) {
		spawnEntity();
	}
}

Entity* EntitySpawner::spawnEntity(Vector3 pos, std::string prefab)
{
	Entity* instance = nullptr;
	json prefabs = MotorCasaPaco::getInstance()->getResourceManager()->getPrefabs();
	std::string prfb = prefab;

	int id;

	if (idsUnused.empty())
		id = items.size() + 1;
	else
		id = idsUnused.back();

	if (prfb == "") prfb = defaultPrefab;

	if (!prefabs[prfb].is_null()) {
		json aux = prefabs[prfb];
		instance = new Entity(MotorCasaPaco::getInstance()->getSceneManager()->getCurrentScene(), prfb + "_" + std::to_string(id));
		aux["name"] = instance->getName();
		instance->init(aux);
		if (!aux["components"].is_null() && aux["components"].is_array()) {
			std::vector<json> e = aux["components"];
				for (json c : e) {
					instance->addComponentFromJson(c);
				}
		}
		instance->getComponent<Transform>("Transform")->setPosition(pos);
		if (!idsUnused.empty() && id == idsUnused.back()) idsUnused.pop_back();
		items.push_back({ instance, id });
	}
	return instance;
}
