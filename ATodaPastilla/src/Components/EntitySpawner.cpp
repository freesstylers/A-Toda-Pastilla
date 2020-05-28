#include "Components/EntitySpawner.h"
#include "Entity/Entity.h"
#include "Entity/Transform.h"
#include "MotorCasaPaco.h"
#include "Resources/ResourceManager.h"
#include "Scene/SceneManager.h"
#include "Input/InputManager.h"
#include "Input/PacoKeys.h"
#include <string>
#include "checkML.h"

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
}

Entity* EntitySpawner::spawnEntity(Vector3 pos, std::string prefab)
{
	Entity* instance = nullptr;
	json prefabs = MotorCasaPaco::getInstance()->getResourceManager()->getPrefabs();
	std::string prfb = prefab;

	if (prfb == "") prfb = defaultPrefab;

	if (!prefabs[prfb].is_null()) {
		json aux = prefabs[prfb];
		instance=MotorCasaPaco::getInstance()->getSceneManager()->getCurrentScene()->addEntity(prfb);
		aux["name"] = instance->getName();
		instance->init(aux);

		if(!aux["tag"].is_null())
			instance->setTag(aux["tag"]);

		if (!aux["components"].is_null() && aux["components"].is_array()) {
			std::vector<json> e = aux["components"];
				for (json c : e) {
					instance->addComponentFromJson(c);
				}
		}
		instance->getComponent<Transform>("Transform")->setPosition(pos);
		instance->setEnabled(true);
	}
	return instance;
}
