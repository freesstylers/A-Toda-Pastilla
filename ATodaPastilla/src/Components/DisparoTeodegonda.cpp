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

	if (!j["maximumChargeSound"].is_null()) {
		if (!j["maximumChargeSound"].is_array()) {
			for (int i = 0; i < shotModes.size(); i++) {
				std::string inter = j["maximumChargeSound"];
				shotModes[i].maximumChargeSound = inter;
			}
		}
		else {
			for (int i = 0; i < shotModes.size(); i++) {
				std::string inter = j["maximumChargeSound"][i];
				shotModes[i].maximumChargeSound = inter;
			}
		}
	}

	for (int i = 0; i < nModes; i++) {
		shotModes[i].nBullets = std::vector<int>(shotModes[i].chargeLevels, 0);
		shotModes[i].damagePerBullet = std::vector<float>(shotModes[i].chargeLevels, 0);
		shotModes[i].bulletSpeed = std::vector<float>(shotModes[i].chargeLevels, 0);
		shotModes[i].dispersionAngle = std::vector<float>(shotModes[i].chargeLevels, 0);
		shotModes[i].inaccuracy = std::vector<float>(shotModes[i].chargeLevels, 0);
		shotModes[i].inacDispersion = std::vector<float>(shotModes[i].chargeLevels, 0);
		shotModes[i].burstCadence = std::vector<float>(shotModes[i].chargeLevels, 0);
		shotModes[i].burstShots = std::vector<int>(shotModes[i].chargeLevels,  0);
		shotModes[i].shotSound = std::vector<std::string>(shotModes[i].chargeLevels, "");
		shotModes[i].chargeSound = std::vector<std::string>(shotModes[i].chargeLevels, "");
	}
	if (!j["chargeSound"].is_null()) {
		if (!j["chargeSound"].is_array()) {
			for (int i = 0; i < shotModes.size(); i++) {
				for (int s = 0; s < shotModes[i].chargeLevels; s++){
					std::string inter = j["chargeSound"];
					shotModes[i].chargeSound[s] = inter;
				}
			}
		}
		else {
			int ModeSiz=shotModes.size();
			if (j["chargeSound"].size() < ModeSiz) ModeSiz = j["chargeSound"].size();
			for (int i = 0; i < ModeSiz; i++) {
				if (!j["chargeSound"][i].is_array()) {
					for (int s = 0; s < shotModes[i].chargeLevels; s++) {
						std::string inter = j["chargeSound"][i];
						shotModes[i].chargeSound[s] = inter;
					}
				}
				else {
					int LvlSiz = shotModes[i].chargeLevels;
					if (j["chargeSound"][i].size() < LvlSiz) LvlSiz = j["chargeSound"][i].size();
					for (int s = 0; s < LvlSiz; s++) {
						std::string inter = j["chargeSound"][i][s];
						shotModes[i].chargeSound[s] = inter;
					}
					if (LvlSiz < shotModes[i].chargeLevels) {
						for (int s = LvlSiz; s < shotModes[i].chargeLevels; s++) {
							shotModes[i].chargeSound[s] = shotModes[i].chargeSound[LvlSiz - 1];
						}
					}
				}
			}
			if (ModeSiz < shotModes.size()) {
				for (int i = ModeSiz; i < shotModes.size(); i++) {
					for(int s=0; s<shotModes[i].chargeLevels; s++)
						shotModes[i].chargeSound[s] = shotModes[ModeSiz-1].chargeSound[s];
				}
			}
		}
	}

	if (!j["shotSound"].is_null()) {
		if (!j["shotSound"].is_array()) {
			for (int i = 0; i < shotModes.size(); i++) {
				for (int s = 0; s < shotModes[i].chargeLevels; s++) {
					std::string inter = j["shotSound"];
					shotModes[i].shotSound[s] = inter;
				}
			}
		}
		else {
			int ModeSiz = shotModes.size();
			if (j["shotSound"].size() < ModeSiz) ModeSiz = j["shotSound"].size();
			for (int i = 0; i < ModeSiz; i++) {
				if (!j["shotSound"][i].is_array()) {
					for (int s = 0; s < shotModes[i].chargeLevels; s++) {
						std::string inter = j["shotSound"][i];
						shotModes[i].shotSound[s] = inter;
					}
				}
				else {
					int LvlSiz = shotModes[i].chargeLevels;
					if (j["shotSound"][i].size() < LvlSiz) LvlSiz = j["shotSound"][i].size();
					for (int s = 0; s < LvlSiz; s++) {
						std::string inter = j["shotSound"][i][s];
						shotModes[i].shotSound[s] = inter;
					}
					if (LvlSiz < shotModes[i].chargeLevels) {
						for (int s = LvlSiz; s < shotModes[i].chargeLevels; s++) {
							shotModes[i].shotSound[s] = shotModes[i].shotSound[LvlSiz - 1];
						}
					}
				}
			}
			if (ModeSiz < shotModes.size()) {
				for (int i = ModeSiz; i < shotModes.size(); i++) {
					for (int s = 0; s < shotModes[i].chargeLevels; s++)
						shotModes[i].shotSound[s] = shotModes[ModeSiz - 1].shotSound[s];
				}
			}
		}
	}

	if (!j["nBullets"].is_null()) {
		if (!j["nBullets"].is_array()) {
			for (int i = 0; i < shotModes.size(); i++) {
				for (int s = 0; s < shotModes[i].chargeLevels; s++) {
					shotModes[i].nBullets[s] = j["nBullets"];
				}
			}
		}
		else {
			int ModeSiz = shotModes.size();
			if (j["nBullets"].size() < ModeSiz) ModeSiz = j["nBullets"].size();
			for (int i = 0; i < ModeSiz; i++) {
				if (!j["nBullets"][i].is_array()) {
					for (int s = 0; s < shotModes[i].chargeLevels; s++) {
						shotModes[i].nBullets[s] = j["nBullets"][i];

					}
				}
				else {
					int LvlSiz = shotModes[i].chargeLevels;
					if (j["nBullets"][i].size() < LvlSiz) LvlSiz = j["nBullets"][i].size();
					for (int s = 0; s < LvlSiz; s++) {
						shotModes[i].nBullets[s] = j["nBullets"][i][s];
					}
					if (LvlSiz < shotModes[i].chargeLevels) {
						for (int s = LvlSiz; s < shotModes[i].chargeLevels; s++) {
							shotModes[i].nBullets[s] = shotModes[i].nBullets[LvlSiz - 1];
						}
					}
				}
			}
			if (ModeSiz < shotModes.size()) {
				for (int i = ModeSiz; i < shotModes.size(); i++) {
					for (int s = 0; s < shotModes[i].chargeLevels; s++)
						shotModes[i].nBullets[s] = shotModes[ModeSiz - 1].nBullets[s];
				}
			}
		}
	}

	if (!j["damagePerBullet"].is_null()) {
		if (!j["damagePerBullet"].is_array()) {
			for (int i = 0; i < shotModes.size(); i++) {
				for (int s = 0; s < shotModes[i].chargeLevels; s++) {
					shotModes[i].damagePerBullet[s] = j["damagePerBullet"];
				}
			}
		}
		else {
			int ModeSiz = shotModes.size();
			if (j["damagePerBullet"].size() < ModeSiz) ModeSiz = j["damagePerBullet"].size();
			for (int i = 0; i < ModeSiz; i++) {
				if (!j["damagePerBullet"][i].is_array()) {
					for (int s = 0; s < shotModes[i].chargeLevels; s++) {
						shotModes[i].damagePerBullet[s] = j["damagePerBullet"][i];

					}
				}
				else {
					int LvlSiz = shotModes[i].chargeLevels;
					if (j["damagePerBullet"][i].size() < LvlSiz) LvlSiz = j["damagePerBullet"][i].size();
					for (int s = 0; s < LvlSiz; s++) {
						shotModes[i].damagePerBullet[s] = j["damagePerBullet"][i][s];
					}
					if (LvlSiz < shotModes[i].chargeLevels) {
						for (int s = LvlSiz; s < shotModes[i].chargeLevels; s++) {
							shotModes[i].damagePerBullet[s] = shotModes[i].damagePerBullet[LvlSiz - 1];
						}
					}
				}
			}
			if (ModeSiz < shotModes.size()) {
				for (int i = ModeSiz; i < shotModes.size(); i++) {
					for (int s = 0; s < shotModes[i].chargeLevels; s++)
						shotModes[i].damagePerBullet[s] = shotModes[ModeSiz - 1].damagePerBullet[s];
				}
			}
		}
	}
	

	if (!j["bulletSpeed"].is_null()) {
		if (!j["bulletSpeed"].is_array()) {
			for (int i = 0; i < shotModes.size(); i++) {
				for (int s = 0; s < shotModes[i].chargeLevels; s++) {
					shotModes[i].bulletSpeed[s] = j["bulletSpeed"];
				}
			}
		}
		else {
			int ModeSiz = shotModes.size();
			if (j["bulletSpeed"].size() < ModeSiz) ModeSiz = j["bulletSpeed"].size();
			for (int i = 0; i < ModeSiz; i++) {
				if (!j["bulletSpeed"][i].is_array()) {
					for (int s = 0; s < shotModes[i].chargeLevels; s++) {
						shotModes[i].bulletSpeed[s] = j["bulletSpeed"][i];

					}
				}
				else {
					int LvlSiz = shotModes[i].chargeLevels;
					if (j["bulletSpeed"][i].size() < LvlSiz) LvlSiz = j["bulletSpeed"][i].size();
					for (int s = 0; s < LvlSiz; s++) {
						shotModes[i].bulletSpeed[s] = j["bulletSpeed"][i][s];
					}
					if (LvlSiz < shotModes[i].chargeLevels) {
						for (int s = LvlSiz; s < shotModes[i].chargeLevels; s++) {
							shotModes[i].bulletSpeed[s] = shotModes[i].bulletSpeed[LvlSiz - 1];
						}
					}
				}
			}
			if (ModeSiz < shotModes.size()) {
				for (int i = ModeSiz; i < shotModes.size(); i++) {
					for (int s = 0; s < shotModes[i].chargeLevels; s++)
						shotModes[i].bulletSpeed[s] = shotModes[ModeSiz - 1].bulletSpeed[s];
				}
			}
		}
	}

	if (!j["dispersionAngle"].is_null()) {
		if (!j["dispersionAngle"].is_array()) {
			for (int i = 0; i < shotModes.size(); i++) {
				for (int s = 0; s < shotModes[i].chargeLevels; s++) {
					shotModes[i].dispersionAngle[s] = j["dispersionAngle"];
				}
			}
		}
		else {
			int ModeSiz = shotModes.size();
			if (j["dispersionAngle"].size() < ModeSiz) ModeSiz = j["dispersionAngle"].size();
			for (int i = 0; i < ModeSiz; i++) {
				if (!j["dispersionAngle"][i].is_array()) {
					for (int s = 0; s < shotModes[i].chargeLevels; s++) {
						shotModes[i].dispersionAngle[s] = j["dispersionAngle"][i];

					}
				}
				else {
					int LvlSiz = shotModes[i].chargeLevels;
					if (j["dispersionAngle"][i].size() < LvlSiz) LvlSiz = j["dispersionAngle"][i].size();
					for (int s = 0; s < LvlSiz; s++) {
						shotModes[i].dispersionAngle[s] = j["dispersionAngle"][i][s];
					}
					if (LvlSiz < shotModes[i].chargeLevels) {
						for (int s = LvlSiz; s < shotModes[i].chargeLevels; s++) {
							shotModes[i].dispersionAngle[s] = shotModes[i].dispersionAngle[LvlSiz - 1];
						}
					}
				}
			}
			if (ModeSiz < shotModes.size()) {
				for (int i = ModeSiz; i < shotModes.size(); i++) {
					for (int s = 0; s < shotModes[i].chargeLevels; s++)
						shotModes[i].dispersionAngle[s] = shotModes[ModeSiz - 1].dispersionAngle[s];
				}
			}
		}
	}

	if (!j["inaccuracy"].is_null()) {
		if (!j["inaccuracy"].is_array()) {
			for (int i = 0; i < shotModes.size(); i++) {
				for (int s = 0; s < shotModes[i].chargeLevels; s++) {
					shotModes[i].inaccuracy[s] = j["inaccuracy"];
				}
			}
		}
		else {
			int ModeSiz = shotModes.size();
			if (j["inaccuracy"].size() < ModeSiz) ModeSiz = j["inaccuracy"].size();
			for (int i = 0; i < ModeSiz; i++) {
				if (!j["inaccuracy"][i].is_array()) {
					for (int s = 0; s < shotModes[i].chargeLevels; s++) {
						shotModes[i].inaccuracy[s] = j["inaccuracy"][i];

					}
				}
				else {
					int LvlSiz = shotModes[i].chargeLevels;
					if (j["inaccuracy"][i].size() < LvlSiz) LvlSiz = j["inaccuracy"][i].size();
					for (int s = 0; s < LvlSiz; s++) {
						shotModes[i].inaccuracy[s] = j["inaccuracy"][i][s];
					}
					if (LvlSiz < shotModes[i].chargeLevels) {
						for (int s = LvlSiz; s < shotModes[i].chargeLevels; s++) {
							shotModes[i].inaccuracy[s] = shotModes[i].inaccuracy[LvlSiz - 1];
						}
					}
				}
			}
			if (ModeSiz < shotModes.size()) {
				for (int i = ModeSiz; i < shotModes.size(); i++) {
					for (int s = 0; s < shotModes[i].chargeLevels; s++)
						shotModes[i].inaccuracy[s] = shotModes[ModeSiz - 1].inaccuracy[s];
				}
			}
		}
	}

	if (!j["inacDispersion"].is_null()) {
		if (!j["inacDispersion"].is_array()) {
			for (int i = 0; i < shotModes.size(); i++) {
				for (int s = 0; s < shotModes[i].chargeLevels; s++) {
					shotModes[i].inacDispersion[s] = j["inacDispersion"];
				}
			}
		}
		else {
			int ModeSiz = shotModes.size();
			if (j["inacDispersion"].size() < ModeSiz) ModeSiz = j["inacDispersion"].size();
			for (int i = 0; i < ModeSiz; i++) {
				if (!j["inacDispersion"][i].is_array()) {
					for (int s = 0; s < shotModes[i].chargeLevels; s++) {
						shotModes[i].inacDispersion[s] = j["inacDispersion"][i];

					}
				}
				else {
					int LvlSiz = shotModes[i].chargeLevels;
					if (j["inacDispersion"][i].size() < LvlSiz) LvlSiz = j["inacDispersion"][i].size();
					for (int s = 0; s < LvlSiz; s++) {
						shotModes[i].inacDispersion[s] = j["inacDispersion"][i][s];
					}
					if (LvlSiz < shotModes[i].chargeLevels) {
						for (int s = LvlSiz; s < shotModes[i].chargeLevels; s++) {
							shotModes[i].inacDispersion[s] = shotModes[i].inacDispersion[LvlSiz - 1];
						}
					}
				}
			}
			if (ModeSiz < shotModes.size()) {
				for (int i = ModeSiz; i < shotModes.size(); i++) {
					for (int s = 0; s < shotModes[i].chargeLevels; s++)
						shotModes[i].inacDispersion[s] = shotModes[ModeSiz - 1].inacDispersion[s];
				}
			}
		}
	}

	if (!j["burstCadence"].is_null()) {
		if (!j["burstCadence"].is_array()) {
			for (int i = 0; i < shotModes.size(); i++) {
				for (int s = 0; s < shotModes[i].chargeLevels; s++) {
					shotModes[i].burstCadence[s] = j["burstCadence"];
				}
			}
		}
		else {
			int ModeSiz = shotModes.size();
			if (j["burstCadence"].size() < ModeSiz) ModeSiz = j["burstCadence"].size();
			for (int i = 0; i < ModeSiz; i++) {
				if (!j["burstCadence"][i].is_array()) {
					for (int s = 0; s < shotModes[i].chargeLevels; s++) {
						shotModes[i].burstCadence[s] = j["burstCadence"][i];

					}
				}
				else {
					int LvlSiz = shotModes[i].chargeLevels;
					if (j["burstCadence"][i].size() < LvlSiz) LvlSiz = j["burstCadence"][i].size();
					for (int s = 0; s < LvlSiz; s++) {
						shotModes[i].burstCadence[s] = j["burstCadence"][i][s];
					}
					if (LvlSiz < shotModes[i].chargeLevels) {
						for (int s = LvlSiz; s < shotModes[i].chargeLevels; s++) {
							shotModes[i].burstCadence[s] = shotModes[i].burstCadence[LvlSiz - 1];
						}
					}
				}
			}
			if (ModeSiz < shotModes.size()) {
				for (int i = ModeSiz; i < shotModes.size(); i++) {
					for (int s = 0; s < shotModes[i].chargeLevels; s++)
						shotModes[i].burstCadence[s] = shotModes[ModeSiz - 1].burstCadence[s];
				}
			}
		}
	}

	if (!j["burstShots"].is_null()) {
		if (!j["burstShots"].is_array()) {
			for (int i = 0; i < shotModes.size(); i++) {
				for (int s = 0; s < shotModes[i].chargeLevels; s++) {
					shotModes[i].burstShots[s] = j["burstShots"];
				}
			}
		}
		else {
			int ModeSiz = shotModes.size();
			if (j["burstShots"].size() < ModeSiz) ModeSiz = j["burstShots"].size();
			for (int i = 0; i < ModeSiz; i++) {
				if (!j["burstShots"][i].is_array()) {
					for (int s = 0; s < shotModes[i].chargeLevels; s++) {
						shotModes[i].burstShots[s] = j["burstShots"][i];

					}
				}
				else {
					int LvlSiz = shotModes[i].chargeLevels;
					if (j["burstShots"][i].size() < LvlSiz) LvlSiz = j["burstShots"][i].size();
					for (int s = 0; s < LvlSiz; s++) {
						shotModes[i].burstShots[s] = j["burstShots"][i][s];
					}
					if (LvlSiz < shotModes[i].chargeLevels) {
						for (int s = LvlSiz; s < shotModes[i].chargeLevels; s++) {
							shotModes[i].burstShots[s] = shotModes[i].burstShots[LvlSiz - 1];
						}
					}
				}
			}
			if (ModeSiz < shotModes.size()) {
				for (int i = ModeSiz; i < shotModes.size(); i++) {
					for (int s = 0; s < shotModes[i].chargeLevels; s++)
						shotModes[i].burstShots[s] = shotModes[ModeSiz - 1].burstShots[s];
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
				AudioManager::getInstance()->playMusic(shotModes[currMode].maximumChargeSound.c_str(), 3);
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
