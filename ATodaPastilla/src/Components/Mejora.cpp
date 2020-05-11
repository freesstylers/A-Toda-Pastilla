
#include "Scene/SceneManager.h"
#include "MotorCasaPaco.h"
#include "Physics/RigidBody.h"
#include "Components/GameManager.h"
#include "Entity/Entity.h"
#include "Entity/Transform.h"
#include "Audio/AudioManager.h"
#include "Components/Mejora.h"
#include <math.h>


Mejora::Mejora(json& args) : Component(args)
{

}

Mejora::~Mejora()
{

}

void Mejora::init(json& j)
{

	
}

void Mejora::OnCollision(Entity* ent)
{
	if (ent->getTag() == "Player")
	{
		getEntity()->setEnabled(false);
	}
}

void Mejora::update()
{
	e_->getComponent<Transform>("Transform")->setPosition(e_->getComponent<Transform>("Transform")->getPosition() +
		Vector3(sin(MotorCasaPaco::getInstance()->getTime() * sinusoidalFrequency) * sinusoidalMagnitude, 0, movVertical) * MotorCasaPaco::getInstance()->DeltaTime());

}