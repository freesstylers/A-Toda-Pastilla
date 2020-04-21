#include "Components/EntitySpawner.h"
#include "Entity/Entity.h"
#include "Scene/SceneManager.h"
#include "Resources/ResourceManager.h"

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
		if (!(*i)->getActive()) {
			delete *i;
			items.erase(i);
		}
		i = aux;
	}
}

Entity* EntitySpawner::spawnEntity(std::string prefab)
{
	json prefabs=ResourceManager::getInstance()->getPrefabs();
	return nullptr;
}
