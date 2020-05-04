#include "Components/DisparoTeogonda.h"
#include "MotorCasaPaco.h"
#include "Input/InputManager.h"
#include "Entity/Transform.h"


DisparoTeogonda::DisparoTeogonda(json& args):ProjectileSpawner(args)
{
}

void DisparoTeogonda::init(json& j)
{
	ProjectileSpawner::init(j);

	teoModes = std::vector<TeogondaShotInfo>(nModes);

	if (!j["chargeLevels"].is_null()) {
		if (!j["chargeLevels"].is_array()) {
			for (int i = 0; i < teoModes.size(); i++) {
				teoModes[i].chargeLevels = j["chargeLevels"];
			}
		}
		else {
			for (int i = 0; i < teoModes.size(); i++) {
				teoModes[i].chargeLevels = j["chargeLevels"][i];
			}
		}
	}

	for (int i = 0; i < nModes; i++) {
		teoModes[i].burstCadence = std::vector<float>(teoModes[i].chargeLevels);
		teoModes[i].burstShots = std::vector<int>(teoModes[i].chargeLevels);
	}

	if (!j["chargeTime"].is_null()) {
		if (!j["chargeTime"].is_array()) {
			for (int i = 0; i < teoModes.size(); i++) {
				teoModes[i].chargeTime = j["chargeTime"];
			}
		}
		else {
			for (int i = 0; i < teoModes.size(); i++) {
				teoModes[i].chargeTime = j["chargeTime"][i];
			}
		}
	}


	if (!j["burstCadence"].is_null()) {
		if (!j["burstCadence"].is_array()) {
			for (int i = 0; i < teoModes.size(); i++) {
				for (int s = 0; s < teoModes[i].burstCadence.size(); s++) {
					teoModes[i].burstCadence[s]=j["burstCadence"];
				}
			}
		}
		else if(!j["burstCadence"][0].is_array()){
			for (int i = 0; i < teoModes.size(); i++) {
				for (int s = 0; s < teoModes[i].burstCadence.size(); s++) {
					teoModes[i].burstCadence[s] = j["burstCadence"][i];
				}
			}
		}
		else {
			for (int i = 0; i < teoModes.size(); i++) {
				for (int s = 0; s < teoModes[i].burstCadence.size(); s++) {
					teoModes[i].burstCadence[s] = j["burstCadence"][i][s];
				}
			}
		}
	}
	if (!j["burstShots"].is_null()) {
		if (!j["burstShots"].is_array()) {
			for (int i = 0; i < teoModes.size(); i++) {
				for (int s = 0; s < teoModes[i].burstShots.size(); s++) {
					teoModes[i].burstShots[s] = j["burstShots"];
				}
			}
		}
		else if (!j["burstShots"][0].is_array()) {
			for (int i = 0; i < teoModes.size(); i++) {
				for (int s = 0; s < teoModes[i].burstShots.size(); s++) {
					teoModes[i].burstShots[s] = j["burstShots"][i];
				}
			}
		}
		else {
			for (int i = 0; i < teoModes.size(); i++) {
				for (int s = 0; s < teoModes[i].burstShots.size(); s++) {
					teoModes[i].burstShots[s] = j["burstShots"][i][s];
				}
			}
		}
	}
	
}

void DisparoTeogonda::start()
{
	currMode = 0;
	burstShotsFired = 0;
	timeCharged = 0;
	currChargeLevel = -1;
}

void DisparoTeogonda::update()
{
	std::cout << "ShotsFired: " << burstShotsFired << "chargeLevel: " << currChargeLevel;
	if(currChargeLevel>=0)
		std::cout << "burstShots: "<<teoModes[currMode].burstShots[currChargeLevel];

	std::cout << "\n";
	if (MotorCasaPaco::getInstance()->getInputManager()->GameControllerIsButtonDown(CONTROLLER_BUTTON_A)) {
		chargeShot();
	}
	else {
		fireBurst();
		timeCharged = 0;
	}
}

bool DisparoTeogonda::ReceiveEvent(Event& event)
{
	if (event.type == "PAUSE")
		setEnabled(!isEnabled());

	return false;
}


void DisparoTeogonda::chargeShot()
{
	timeCharged += MotorCasaPaco::getInstance()->DeltaTime();

	if (timeCharged >= teoModes[currMode].chargeTime) {

		if (currChargeLevel < teoModes[currMode].chargeLevels - 1)
			currChargeLevel++;
		timeCharged = 0;
	}

	if (currChargeLevel >= 0)
		timeSinceLastShot = teoModes[currMode].burstCadence[currChargeLevel];
	
}

void DisparoTeogonda::fireBurst()
{
	if (currChargeLevel >= 0 && timeSinceLastShot >= teoModes[currMode].burstCadence[currChargeLevel] 
		&& burstShotsFired < teoModes[currMode].burstShots[currChargeLevel]) {

		spawnProjectiles(getEntity()->getComponent<Transform>("Transform")->getPosition() + shotModes[currMode].shotPos,
			shotModes[currMode].shotDir, shotModes[currMode].bulletSpeed, shotModes[currMode].nBullets,
			shotModes[currMode].dispersionAngle, shotModes[currMode].inaccuracy, shotModes[currMode].inacDispersion);
		burstShotsFired++;
		timeSinceLastShot = 0;
	}
	if (currChargeLevel>= 0 &&  burstShotsFired >= teoModes[currMode].burstShots[currChargeLevel]) {
		currChargeLevel = -1;
		burstShotsFired = 0;
	}
	timeSinceLastShot += MotorCasaPaco::getInstance()->DeltaTime();
}
