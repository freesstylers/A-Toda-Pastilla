
#include "Scene/SceneManager.h"
#include "MotorCasaPaco.h"
#include "Physics/RigidBody.h"
#include "Components/GameManager.h"
#include "Entity/Entity.h"
#include "Entity/Transform.h"
#include "Audio/AudioManager.h"
#include "Components/MejoraDisparo.h"
#include "Components/ProjectileSpawner.h"
#include "Components/DisparoTeodegonda.h"
#include "Components/DisparoWiterico.h"
#include <math.h>


MejoraDisparo::MejoraDisparo(json& args) : Mejora(args)
{

}

MejoraDisparo::~MejoraDisparo()
{

}

void MejoraDisparo::init(json& j)
{
	Mejora::init(j);
	
}

void MejoraDisparo::OnCollision(Entity* ent)
{
	if (ent->getTag() == "Player")
	{
		EventManager::getInstance()->EmitEvent("MejoraDisparo");
		if (ent->getComponent<DisparoWiterico>("DisparoWiterico") == nullptr) {
			if (ent->getComponent<DisparoTeodegonda>("DisparoTeodegonda")->getNmodes() >=
				ent->getComponent<DisparoTeodegonda>("DisparoTeodegonda")->getShotMode()) {
				ent->getComponent<DisparoTeodegonda>("DisparoTeodegonda")->setShotMode(ent->getComponent<DisparoTeodegonda>("DisparoTeodegonda")->getShotMode() + 1);
			}
		}
		else {
			if (ent->getComponent<DisparoWiterico>("DisparoWiterico")->getNmodes() >=
				ent->getComponent<DisparoWiterico>("DisparoWiterico")->getShotMode()) {
				ent->getComponent<DisparoWiterico>("DisparoWiterico")->setShotMode(ent->getComponent<DisparoWiterico>("DisparoWiterico")->getShotMode() + 1);
			}
		}
			getEntity()->setEnabled(false);
	}
}

void MejoraDisparo::update()
{
	Mejora::update();

}