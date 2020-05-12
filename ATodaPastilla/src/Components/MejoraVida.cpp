
#include "Scene/SceneManager.h"
#include "MotorCasaPaco.h"
#include "Physics/RigidBody.h"
#include "Components/GameManager.h"
#include "Entity/Entity.h"
#include "Entity/Transform.h"
#include "Audio/AudioManager.h"
#include "Components/MejoraVida.h"
#include "Components/ProjectileSpawner.h"
#include "Components/Vida.h"
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
		if (ent->getComponent<Vida>("Vida")->GetVida() <
				2) {
			ent->getComponent<Vida>("Vida")->sumaVida(1);
		}
			getEntity()->setEnabled(false);
	}
}

void MejoraVida::update()
{
	Mejora::update();

}