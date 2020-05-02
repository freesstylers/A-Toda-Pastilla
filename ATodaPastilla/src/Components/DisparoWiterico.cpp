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
	if (!j["cadence"].is_null()) {
		float inter = j["cadence"];
		cadence = j["cadence"];
	}
	if (!j["shotPos"].is_null()) {
		float inter = j["shotPos"][0];
		shotPos.X= inter;
		inter = j["shotPos"][1];
		shotPos.Y = inter;
		inter = j["shotPos"][2];
		shotPos.Z = inter;
	}
	if (!j["shotDir"].is_null()) {
		float inter = j["shotDir"][0];
		shotDir.X = inter;
		inter = j["shotDir"][1];
		shotDir.Y = inter;
		inter = j["shotDir"][2];
		shotDir.Z = inter;
	}
	if (!j["nBullets"].is_null()) {
		int inter = j["nBullets"];
		nBullets = j["nBullets"];
	}
	if (!j["bulletSpeed"].is_null()) {
		float inter = j["bulletSpeed"];
		bulletSpeed = j["bulletSpeed"];
	}
	if (!j["dispersionAngle"].is_null()) {
		float inter = j["dispersionAngle"];
		dispersionAngle = j["dispersionAngle"];
	}
}

void DisparoWiterico::start()
{
	timeSinceLastShot = cadence;
}

void DisparoWiterico::update()
{
	if (timeSinceLastShot >= cadence && MotorCasaPaco::getInstance()->getInputManager()->GameControllerIsButtonDown(CONTROLLER_BUTTON_A)) {
		timeSinceLastShot = 0;
		spawnProjectiles(getEntity()->getComponent<Transform>("Transform")->getPosition()+ shotPos, shotDir, bulletSpeed, nBullets, dispersionAngle);
	}
	timeSinceLastShot += MotorCasaPaco::getInstance()->DeltaTime();
}

bool DisparoWiterico::ReceiveEvent(Event& event)
{
	if (event.type == "PAUSE")
		setEnabled(!isEnabled());

	return false;
}
