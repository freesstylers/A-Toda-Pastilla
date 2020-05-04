#include "Components/ProjectileSpawner.h"
#include "Entity/Entity.h"
#include "Components/ProjectileBehaviour.h"
#include "Entity/Transform.h"
#include "MotorCasaPaco.h"

ProjectileSpawner::ProjectileSpawner(json& args):EntitySpawner(args)
{
}

void ProjectileSpawner::init(json& j)
{
	EntitySpawner::init(j);
	nModes = 1;
	if (!j["nModes"].is_null()) {
		nModes = j["nModes"];
	}

	shotModes = std::vector<ShotInfo>(nModes);

	if (!j["cadence"].is_null()) {
		if (!j["cadence"].is_array()) {
			for (int i = 0; i < shotModes.size(); i++) {
				shotModes[i].cadence = j["cadence"];
			}
		}
		else {
			for (int i = 0; i < shotModes.size(); i++) {
				shotModes[i].cadence = j["cadence"][i];
			}
		}
	}
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
	if (!j["shotDir"].is_null()) {
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
	if (!j["nBullets"].is_null() && j["nBullets"].is_array()) {
		if (!j["nBullets"].is_array()) {
			for (int i = 0; i < shotModes.size(); i++) {
				shotModes[i].nBullets = j["nBullets"];
			}
		}
		else {
			for (int i = 0; i < shotModes.size(); i++) {
				shotModes[i].nBullets = j["nBullets"][i];
			}
		}
	}
	if (!j["bulletSpeed"].is_null()) {
		if (!j["bulletSpeed"].is_array()) {
			for (int i = 0; i < shotModes.size(); i++) {
				shotModes[i].bulletSpeed = j["bulletSpeed"];
			}
		}
		else {
			for (int i = 0; i < shotModes.size(); i++) {
				shotModes[i].bulletSpeed = j["bulletSpeed"][i];
			}
		}
	}
	if (!j["dispersionAngle"].is_null()) {
		if (!j["dispersionAngle"].is_array()) {
			for (int i = 0; i < shotModes.size(); i++) {
				shotModes[i].dispersionAngle = j["dispersionAngle"];
			}
		}
		else {
			for (int i = 0; i < shotModes.size(); i++) {
				shotModes[i].dispersionAngle = j["dispersionAngle"][i];
			}
		}
	}
	if (!j["inaccuracy"].is_null()) {
		if (!j["inaccuracy"].is_array()) {
			for (int i = 0; i < shotModes.size(); i++) {
				shotModes[i].inaccuracy = j["inaccuracy"];
			}
		}
		else {
			for (int i = 0; i < shotModes.size(); i++) {
				shotModes[i].inaccuracy = j["inaccuracy"][i];
			}
		}
	}
	if (!j["inacDispersion"].is_null()) {
		if (!j["inacDispersion"].is_array()) {
			for (int i = 0; i < shotModes.size(); i++) {
				shotModes[i].inacDispersion = j["inacDispersion"];
			}
		}
		else {
			for (int i = 0; i < shotModes.size(); i++) {
				shotModes[i].inacDispersion = j["inacDispersion"][i];
			}
		}
	}
}

void ProjectileSpawner::update()
{
}

void ProjectileSpawner::spawnProjectiles(Vector3 pos, Vector3 dir, float speed, int nbullets, float dispersionAngle, float inaccuracy, float inacDispersion, std::string prefab)
{
	float iniAngle = 0;
	Vector3 Dir = dir;
	if (nbullets > 1) {
		iniAngle = dispersionAngle / 2;

		rotateVector(Dir, iniAngle);
	}
	float ang = dispersionAngle / nbullets;

	for (int i = 0; i < nbullets; i++) {
		Entity* prj = spawnEntity(pos, prefab);

		Vector3 inaccSh=Dir;

		calculateInaccuracy(inaccSh, inaccuracy, inacDispersion);

		double rot = dir.Angle(dir, inaccSh) * 180.0 / M_PI;
		if (inaccSh.X > 0) rot *= -1;

		prj->getComponent<Transform>("Transform")->setRotation(Vector3(0, rot, 0));
		prj->getComponent<ProjectileBehaviour>("ProjectileBehaviour")->setDir(inaccSh);
		prj->getComponent<ProjectileBehaviour>("ProjectileBehaviour")->setSpeed(speed);

		rotateVector(Dir, -ang);
	}
}



std::vector<ShotInfo> ProjectileSpawner::getShotModes()
{
	return shotModes;
}

ShotInfo ProjectileSpawner::getCurrentShotMode()
{
	return shotModes[currMode];
}

void ProjectileSpawner::setShotMode(int mode)
{
	if (mode >= 0 && mode < nModes) {
		currMode = mode;
	}
}

void ProjectileSpawner::rotateVector(Vector3& vec, float angle)
{
	vec.X = vec.X * cos(angle * M_PI / 180.0) + vec.Z * sin(angle * M_PI / 180.0);
	vec.Z = vec.Z * sin(angle * M_PI / 180.0) + vec.Z * cos(angle * M_PI / 180.0);
}

void ProjectileSpawner::calculateInaccuracy(Vector3& shot, float inaccuracy, float inacDispersion)
{
	float p = rand() % 100;
	if (p < inaccuracy) {
		float s = rand() % 100;
		float side = 1;

		if (s < 50)
			side = -1;

		rotateVector(shot, inacDispersion * side);
	}
}
