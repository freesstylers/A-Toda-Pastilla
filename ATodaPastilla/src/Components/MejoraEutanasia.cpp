
#include "Scene/SceneManager.h"
#include "MotorCasaPaco.h"
#include "Physics/RigidBody.h"
#include "Components/GameManager.h"
#include "Entity/Entity.h"
#include "Entity/Transform.h"
#include "Audio/AudioManager.h"
#include "Components/MejoraEutanasia.h"
#include "Components/ProjectileSpawner.h"
#include "Components/Vida.h"
#include <math.h>
#include "Graphics/ParticleSystem.h"
#include "checkML.h"

MejoraEutanasia::MejoraEutanasia(json& args) : Mejora(args)
{

}

MejoraEutanasia::~MejoraEutanasia()
{

}

void MejoraEutanasia::init(json& j)
{
	Mejora::init(j);
	
}

void MejoraEutanasia::OnCollision(Entity* ent)
{
	if (ent->getTag() == "Player")
	{	
		ent->getComponent<ParticleSystem>("ParticleSystem")->emit();
		EventManager::getInstance()->EmitEvent("BombaUp");
		std::cout << "Bomba eutanásica goes brrruummm" << std::endl;
		getEntity()->getScene()->deleteEntity(getEntity()->getName());
	}
}

void MejoraEutanasia::update()
{
	Mejora::update();

}