#include "Components/DisparoWiterico.h"
#include "MotorCasaPaco.h"
#include "Input/InputManager.h"
#include "Entity/Transform.h"

DisparoWiterico::DisparoWiterico(json& args):ProjectileSpawner(args)
{
	EventManager::getInstance()->RegisterListener(this, "PAUSE");
}

void DisparoWiterico::init(json& j)
{
	ProjectileSpawner::init(j);
}

void DisparoWiterico::start()
{
	currMode = 0;
	timeSinceLastShot = shotModes[currMode].cadence;

}

void DisparoWiterico::update()
{
	if (MotorCasaPaco::getInstance()->getInputManager()->GameControllerIsButtonDown(CONTROLLER_BUTTON_B)) {
		setShotMode(2);
	}
	if (MotorCasaPaco::getInstance()->getInputManager()->GameControllerIsButtonDown(CONTROLLER_BUTTON_Y)) {
		setShotMode(1);
	}
	if (MotorCasaPaco::getInstance()->getInputManager()->GameControllerIsButtonDown(CONTROLLER_BUTTON_X)) {
		setShotMode(0);
	}
	if (timeSinceLastShot >= shotModes[currMode].cadence && MotorCasaPaco::getInstance()->getInputManager()->GameControllerIsButtonDown(CONTROLLER_BUTTON_A)) {
		timeSinceLastShot = 0;
		spawnProjectiles(getEntity()->getComponent<Transform>("Transform")->getPosition() + shotModes[currMode].shotPos,
			shotModes[currMode].shotDir, shotModes[currMode].bulletSpeed, shotModes[currMode].nBullets,
			shotModes[currMode].dispersionAngle, shotModes[currMode].inaccuracy, shotModes[currMode].inacDispersion);
	}
	timeSinceLastShot += MotorCasaPaco::getInstance()->DeltaTime();
}

bool DisparoWiterico::ReceiveEvent(Event& event)
{
	if (event.type == "PAUSE")
		setEnabled(!isEnabled());

	return false;
}
