
#include "Scene/SceneManager.h"
#include "MotorCasaPaco.h"
#include "Physics/RigidBody.h"
#include "Components/GameManager.h"
#include "Entity/Entity.h"
#include "Entity/Transform.h"
#include "Audio/AudioManager.h"
#include "Components/MejoraVida.h"
#include "Components/ProjectileSpawner.h"
#include "Components/VidaPlayer.h"
#include <math.h>


MejoraVida::MejoraVida(json& args) : Mejora(args)
{

}

MejoraVida::~MejoraVida()
{

}

void MejoraVida::init(json& j)
{
	Mejora::init(j);
	
}

void MejoraVida::OnCollision(Entity* ent)
{
	if (ent->getTag() == "Player")
	{	
		if (ent->getComponent<VidaPlayer>("VidaPlayer")->GetVida() <2) 
		{
			EventManager::getInstance()->EmitEvent("MejoraEscudoUp");
			ent->getComponent<VidaPlayer>("VidaPlayer")->sumaVida(1);
		}
			getEntity()->setEnabled(false);
	}
}

void MejoraVida::update()
{
	Mejora::update();

}