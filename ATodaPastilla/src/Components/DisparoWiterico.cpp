#include "Components/DisparoWiterico.h"
#include "MotorCasaPaco.h"
#include "Input/InputManager.h"
#include "Entity/Transform.h"

DisparoWiterico::DisparoWiterico(json& args):ProjectileSpawner(args)
{

}

void DisparoWiterico::init(json& args)
{
	ProjectileSpawner::init(args);
}

void DisparoWiterico::start()
{
	timeSinceLastShot = cadence;
}

void DisparoWiterico::update()
{
	if (timeSinceLastShot >= cadence && MotorCasaPaco::getInstance()->getInputManager()->IsKeyDown(SCANCODE_E)) {
		timeSinceLastShot = 0;
		spawnProjectiles(getEntity()->getComponent<Transform>("Transform")->getPosition(), Vector3(0, 0, -1), 5, 1);
	}
	timeSinceLastShot += MotorCasaPaco::getInstance()->DeltaTime();
}
