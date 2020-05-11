
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
	if (ent->getTag() == "nave")
	{
		getEntity()->setEnabled(false);
	}
}

void Mejora::update()
{
	float posY = sin( MotorCasaPaco::getInstance()->DeltaTime() );
	e_->getComponent<Transform>("Transform")->translate(Vector3(posY, 0.0f, 0.0f));
	std::cout << e_->getComponent<Transform>("Transform")->getPosition().X << "  " << e_->getComponent<Transform>("Transform")->getPosition().Y << std::endl;
}