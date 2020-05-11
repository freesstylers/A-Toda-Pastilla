#include "Components/DisparoTeodegonda.h"
#include "MotorCasaPaco.h"
#include "Input/InputManager.h"
#include "Entity/Transform.h"
#include "Audio/AudioManager.h"


DisparoTeodegonda::DisparoTeodegonda(json& args):ProjectileSpawner(args)
{
}

void DisparoTeodegonda::init(json& j)
{
	ProjectileSpawner::init(j);

	nModes = 1;
	if (!j["nModes"].is_null()) {
		nModes = j["nModes"];
	}

	shotModes = std::vector<TeodegondaShotInfo>(nModes);

	if (!j["shotPos"].is_null() && j["shotPos"].is_array()) {
		if (!j["shotPos"][0].is_array()) {
			for (int i = 0; i < shotModes.size(); i++) {
				shotModes[i].shotPos.X = j["shotPos"][0];
				shotModes[i].shotPos.Y = j["shotPos"][1];
				shotModes[i].shotPos.Z = j["shotPos"][2];
			}
		}
		else {
			for (int i = 0; i < shotModes.size(); i++) {
				shotModes[i].shotPos.X = j["shotPos"][i][0];
				shotModes[i].shotPos.Y = j["shotPos"][i][1];
				shotModes[i].shotPos.Z = j["shotPos"][i][2];
			}
		}
	}
	if (!j["shotDir"].is_null() && j["shotDir"].is_array()) {
		if (!j["shotDir"][0].is_array()) {
			for (int i = 0; i < shotModes.size(); i++) {
				shotModes[i].shotDir.X = j["shotDir"][0];
				shotModes[i].shotDir.Y = j["shotDir"][1];
				shotModes[i].shotDir.Z = j["shotDir"][2];
			}
		}
		else {
			for (int i = 0; i < shotModes.size(); i++) {
				shotModes[i].shotDir.X = j["shotDir"][i][0];
				shotModes[i].shotDir.Y = j["shotDir"][i][1];
				shotModes[i].shotDir.Z = j["shotDir"][i][2];
			}
		}
	}
	if (!j["chargeLevels"].is_null()) {
		if (!j["chargeLevels"].is_array()) {
			for (int i = 0; i < shotModes.size(); i++) {
				shotModes[i].chargeLevels = j["chargeLevels"];
			}
		}
		else {
			for (int i = 0; i < shotModes.size(); i++) {
				shotModes[i].chargeLevels = j["chargeLevels"][i];
			}
		}
	}
	if (!j["chargeTime"].is_null()) {
		if (!j["chargeTime"].is_array()) {
			for (int i = 0; i < shotModes.size(); i++) {
				shotModes[i].chargeTime = j["chargeTime"];
			}
		}
		else {
			for (int i = 0; i < shotModes.size(); i++) {
				shotModes[i].chargeTime = j["chargeTime"][i];
			}
		}
	}

	for (int i = 0; i < nModes; i++) {
		shotModes[i].nBullets = std::vector<int>(shotModes[i].chargeLevels);
		shotModes[i].damagePerBullet = std::vector<float>(shotModes[i].chargeLevels);
		shotModes[i].bulletSpeed = std::vector<float>(shotModes[i].chargeLevels);
		shotModes[i].dispersionAngle = std::vector<float>(shotModes[i].chargeLevels);
		shotModes[i].inaccuracy = std::vector<float>(shotModes[i].chargeLevels);
		shotModes[i].inacDispersion = std::vector<float>(shotModes[i].chargeLevels);
		shotModes[i].burstCadence = std::vector<float>(shotModes[i].chargeLevels);
		shotModes[i].burstShots = std::vector<int>(shotModes[i].chargeLevels);
		shotModes[i].shotSound = std::vector<std::string>(shotModes[i].chargeLevels);
		shotModes[i].chargeSound = std::vector<std::string>(shotModes[i].chargeLevels);
	}
	if (!j["chargeSound"].is_null()) {
		for (int i = 0; i < shotModes.size(); i++) {
			for (int s = 0; s < shotModes[i].chargeSound.size(); s++) {
				if (j["chargeSound"].is_array() && j["chargeSound"].size() == shotModes.size() &&
					j["chargeSound"][i].is_array() && j["chargeSound"][i].size() == shotModes[i].chargeSound.size()) {
					std::string inter = j["chargeSound"][i][s];
					shotModes[i].chargeSound[s] = inter;
				}
				else if (j["chargeSound"].is_array() && j["chargeSound"].size() == shotModes.size() && !j["chargeSound"][i].is_array()) {
					std::string inter = j["chargeSound"][i];
					shotModes[i].chargeSound[s] = inter;
				}
				else if (!j["chargeSound"].is_array()) {
					std::string inter = j["chargeSound"];
					shotModes[i].chargeSound[s] = inter;
				}
			}
		}
	}

	if (!j["shotSound"].is_null()) {
		for (int i = 0; i < shotModes.size(); i++) {
			for (int s = 0; s < shotModes[i].shotSound.size(); s++) {
				if (j["shotSound"].is_array() && j["shotSound"].size() == shotModes.size() &&
					j["shotSound"][i].is_array() && j["shotSound"][i].size() == shotModes[i].shotSound.size()) {
					std::string inter = j["shotSound"][i][s];
					shotModes[i].shotSound[s] = inter;
				}
				else if (j["shotSound"].is_array() && j["shotSound"].size() == shotModes.size() && !j["shotSound"][i].is_array()) {
					std::string inter = j["shotSound"][i];
					shotModes[i].shotSound[s] = inter;
				}
				else if (!j["shotSound"].is_array()) {
					std::string inter = j["shotSound"];
					shotModes[i].shotSound[s] = inter;
				}
			}
		}
	}

	if (!j["nBullets"].is_null()) {
		for (int i = 0; i < shotModes.size(); i++) {
			for (int s = 0; s < shotModes[i].nBullets.size(); s++) {
				if (j["nBullets"].is_array() && j["nBullets"].size() == shotModes.size() && 
					j["nBullets"][i].is_array() && j["nBullets"][i].size() == shotModes[i].nBullets.size()) {
					shotModes[i].nBullets[s] = j["nBullets"][i][s];
				}
				else if(j["nBullets"].is_array() && j["nBullets"].size() == shotModes.size() && !j["nBullets"][i].is_array()) {
					shotModes[i].nBullets[s] = j["nBullets"][i];
				}
				else if (!j["nBullets"].is_array()) {
					shotModes[i].nBullets[s] = j["nBullets"];
				}
			}
		}
	}

	if (!j["damagePerBullet"].is_null()) {
		for (int i = 0; i < shotModes.size(); i++) {
			for (int s = 0; s < shotModes[i].damagePerBullet.size(); s++) {
				if (j["damagePerBullet"].is_array() && j["damagePerBullet"].size() == shotModes.size() &&
					j["damagePerBullet"][i].is_array() && j["damagePerBullet"][i].size() == shotModes[i].damagePerBullet.size()) {
					shotModes[i].damagePerBullet[s] = j["damagePerBullet"][i][s];
				}
				else if (j["damagePerBullet"].is_array() && j["damagePerBullet"].size() == shotModes.size() && !j["damagePerBullet"][i].is_array()) {
					shotModes[i].damagePerBullet[s] = j["damagePerBullet"][i];
				}
				else if (!j["damagePerBullet"].is_array()) {
					shotModes[i].damagePerBullet[s] = j["damagePerBullet"];
				}
			}
		}
	}
	
	if (!j["bulletSpeed"].is_null()) {
		for (int i = 0; i < shotModes.size(); i++) {
			for (int s = 0; s < shotModes[i].bulletSpeed.size(); s++) {
				if (j["bulletSpeed"].is_array() && j["bulletSpeed"].size() == shotModes.size() &&
					j["bulletSpeed"][i].is_array() && j["bulletSpeed"][i].size() == shotModes[i].bulletSpeed.size()) {
					shotModes[i].bulletSpeed[s] = j["bulletSpeed"][i][s];
				}
				else if (j["bulletSpeed"].is_array() && j["bulletSpeed"].size() == shotModes.size() && !j["bulletSpeed"][i].is_array()) {
					shotModes[i].bulletSpeed[s] = j["bulletSpeed"][i];
				}
				else if(!j["bulletSpeed"].is_array()) {
					shotModes[i].bulletSpeed[s] = j["bulletSpeed"];
				}
			}
		}
	}

	if (!j["dispersionAngle"].is_null()) {
		for (int i = 0; i < shotModes.size(); i++) {
			for (int s = 0; s < shotModes[i].dispersionAngle.size(); s++) {
				if (j["dispersionAngle"].is_array() && j["dispersionAngle"].size() == shotModes.size() &&
					j["dispersionAngle"][i].is_array() && j["dispersionAngle"][i].size() == shotModes[i].dispersionAngle.size()) {
					shotModes[i].dispersionAngle[s] = j["dispersionAngle"][i][s];
				}
				else if (j["dispersionAngle"].is_array() && j["dispersionAngle"].size() == shotModes.size() && !j["dispersionAngle"][i].is_array()) {
					shotModes[i].dispersionAngle[s] = j["dispersionAngle"][i];
				}
				else if (!j["dispersionAngle"].is_array()) {
					shotModes[i].dispersionAngle[s] = j["dispersionAngle"];
				}
			}
		}
	}

	if (!j["inaccuracy"].is_null()) {
		for (int i = 0; i < shotModes.size(); i++) {
			for (int s = 0; s < shotModes[i].inaccuracy.size(); s++) {
				if (j["inaccuracy"].is_array() && j["inaccuracy"].size() == shotModes.size() &&
					j["inaccuracy"][i].is_array() && j["inaccuracy"][i].size() == shotModes[i].inaccuracy.size()) {
					shotModes[i].inaccuracy[s] = j["inaccuracy"][i][s];
				}
				else if (j["inaccuracy"].is_array() && j["inaccuracy"].size() == shotModes.size() && !j["inaccuracy"][i].is_array()) {
					shotModes[i].inaccuracy[s] = j["inaccuracy"][i];
				}
				else if (!j["inaccuracy"].is_array()) {
					shotModes[i].inaccuracy[s] = j["inaccuracy"];
				}
			}
		}
	}

	if (!j["inacDispersion"].is_null()) {
		for (int i = 0; i < shotModes.size(); i++) {
			for (int s = 0; s < shotModes[i].inacDispersion.size(); s++) {
				if (j["inacDispersion"].is_array() && j["inacDispersion"].size() == shotModes.size() &&
					j["inacDispersion"][i].is_array() && j["inacDispersion"][i].size() == shotModes[i].inacDispersion.size()) {
					shotModes[i].inacDispersion[s] = j["inacDispersion"][i][s];
				}
				else if (j["inacDispersion"].is_array() && j["inacDispersion"].size() == shotModes.size() && !j["inacDispersion"][i].is_array()) {
					shotModes[i].inacDispersion[s] = j["inacDispersion"][i];
				}
				else if (!j["inacDispersion"].is_array()) {
					shotModes[i].inacDispersion[s] = j["inacDispersion"];
				}
			}
		}
	}

	if (!j["burstCadence"].is_null()) {
		for (int i = 0; i < shotModes.size(); i++) {
			for (int s = 0; s < shotModes[i].burstCadence.size(); s++) {
				if (j["burstCadence"].is_array() && j["burstCadence"].size() == shotModes.size() &&
					j["burstCadence"][i].is_array() && j["burstCadence"][i].size() == shotModes[i].burstCadence.size()) {
					shotModes[i].dispersionAngle[s] = j["burstCadence"][i][s];
				}
				else if (j["burstCadence"].is_array() && j["burstCadence"].size() == shotModes.size() && !j["burstCadence"][i].is_array()) {
					shotModes[i].burstCadence[s] = j["burstCadence"][i];
				}
				else if (!j["burstCadence"].is_array()) {
					shotModes[i].burstCadence[s] = j["burstCadence"];
				}
			}
		}
	}

	if (!j["burstShots"].is_null()) {
		for (int i = 0; i < shotModes.size(); i++) {
			for (int s = 0; s < shotModes[i].burstShots.size(); s++) {
				if (j["burstShots"].is_array() && j["burstShots"].size() == shotModes.size() &&
					j["burstShots"][i].is_array() && j["burstShots"][i].size() == shotModes[i].burstShots.size()) {
					shotModes[i].burstShots[s] = j["burstShots"][i][s];
				}
				else if (j["burstShots"].is_array() && j["burstShots"].size() == shotModes.size() && !j["burstShots"][i].is_array()) {
					shotModes[i].burstShots[s] = j["burstShots"][i];
				}
				else if (!j["burstShots"].is_array()) {
					shotModes[i].burstShots[s] = j["burstShots"];
				}
			}
		}
	}
	
}

void DisparoTeodegonda::start()
{
	currMode = 0;
	burstShotsFired = 0;
	timeCharged = 0;
	currChargeLevel = -1;
}

void DisparoTeodegonda::update()
{
	if (MotorCasaPaco::getInstance()->getInputManager()->GameControllerIsButtonDown(CONTROLLER_BUTTON_A)) {
		chargeShot();
	}
	else {
		fireBurst();
		timeCharged = 0;
	}
}

bool DisparoTeodegonda::ReceiveEvent(Event& event)
{
	if (event.type == "PAUSE")
		setEnabled(!static_cast<BoolEvent&>(event).flag);

	return false;
}


void DisparoTeodegonda::chargeShot()
{
	timeCharged += MotorCasaPaco::getInstance()->DeltaTime();

	if (timeCharged >= shotModes[currMode].chargeTime) {
		if (currChargeLevel < shotModes[currMode].chargeLevels - 1) {
			currChargeLevel++;
			if (currChargeLevel == shotModes[currMode].chargeLevels - 1)
				AudioManager::getInstance()->playMusic("assets/sound/MaximumCharge.wav", 3);
			else
				AudioManager::getInstance()->playMusic(shotModes[currMode].chargeSound[currChargeLevel].c_str(), 3);
			AudioManager::getInstance()->setVolume(0.05 * (currChargeLevel + 1.0), 3);
		}
		timeCharged = 0;
	}
	if (currChargeLevel >= 0)
		timeSinceLastShot = shotModes[currMode].burstCadence[currChargeLevel];
}

void DisparoTeodegonda::fireBurst()
{
	if (currChargeLevel >= 0 && timeSinceLastShot >= shotModes[currMode].burstCadence[currChargeLevel]
		&& burstShotsFired < shotModes[currMode].burstShots[currChargeLevel]) {

		spawnProjectiles(getEntity()->getComponent<Transform>("Transform")->getPosition() + shotModes[currMode].shotPos,
			shotModes[currMode].shotDir, shotModes[currMode].bulletSpeed[currChargeLevel], shotModes[currMode].nBullets[currChargeLevel],
			shotModes[currMode].damagePerBullet[currChargeLevel], shotModes[currMode].dispersionAngle[currChargeLevel], 
			shotModes[currMode].inaccuracy[currChargeLevel], shotModes[currMode].inacDispersion[currChargeLevel]);
		burstShotsFired++;
		timeSinceLastShot = 0;
		MotorCasaPaco::getInstance()->getAudioManager()->playMusic(shotModes[currMode].shotSound[currChargeLevel].c_str(), 3);
		MotorCasaPaco::getInstance()->getAudioManager()->setVolume(0.05 * (currChargeLevel+1.0), 3);

	}
	if (currChargeLevel>= 0 &&  burstShotsFired >= shotModes[currMode].burstShots[currChargeLevel]) {
		currChargeLevel = -1;
		burstShotsFired = 0;
	}
	timeSinceLastShot += MotorCasaPaco::getInstance()->DeltaTime();
}
