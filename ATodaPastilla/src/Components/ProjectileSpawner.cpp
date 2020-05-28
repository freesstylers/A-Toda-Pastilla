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
}

void ProjectileSpawner::update()
{
}

void ProjectileSpawner::spawnProjectiles(Vector3 pos, Vector3 dir, float speed, int nbullets, float damage, float dispersionAngle, float inaccuracy, float inacDispersion, std::string prefab)
{
	float iniAngle = 0;
	Vector3 Dir = dir;
	if (nbullets > 1) {
		iniAngle = dispersionAngle / 2;

		rotateVector(Dir, iniAngle);
	}
	float ang = dispersionAngle / nbullets;

	for (int i = 0; i < nbullets; i++) {
		Entity* prj = spawnEntity(e_->getComponent<Transform>("Transform")->getPosition() + pos, prefab);

		Vector3 inaccSh=Dir;

		calculateInaccuracy(inaccSh, inaccuracy, inacDispersion);


		double auxAng;
		Vector3 prevRot;
		Quaternion::ToAngleAxis(prj->getComponent<Transform>("Transform")->getRotation(), auxAng, prevRot);

		double rot = dir.Angle(dir, inaccSh) * 180.0 / M_PI;
		if (inaccSh.X > 0) rot *= -1;

		prj->getComponent<Transform>("Transform")->setRotation(prevRot * auxAng + Vector3(0, rot, 0));
		prj->getComponent<ProjectileBehaviour>("ProjectileBehaviour")->setDir(inaccSh);
		prj->getComponent<ProjectileBehaviour>("ProjectileBehaviour")->setSpeed(speed);
		prj->getComponent<ProjectileBehaviour>("ProjectileBehaviour")->setDamage(damage);
		prj->getComponent<ProjectileBehaviour>("ProjectileBehaviour")->setSource(getEntity()->getTag());

		rotateVector(Dir, -ang);
	}
}

void ProjectileSpawner::spawnEutanasia()
{
	Vector3 dir = Vector3(0, 0, -1);
	Vector3 pos = Vector3(0, 0, -50);
	rotateVector(dir, 0);
	Entity* bomba = spawnEntity(e_->getComponent<Transform>("Transform")->getPosition() + pos, "Eutanasia");

	bomba->setTag("Bomba");
	bomba->getComponent<ProjectileBehaviour>("ProjectileBehaviour")->setDir(dir);
	bomba->getComponent<ProjectileBehaviour>("ProjectileBehaviour")->setSpeed(100);
	bomba->getComponent<ProjectileBehaviour>("ProjectileBehaviour")->setDamage(100);
	bomba->getComponent<ProjectileBehaviour>("ProjectileBehaviour")->setSource(getEntity()->getTag());
}
void ProjectileSpawner::setShotMode(int mode)
{
	if (mode >= 0 && mode < nModes) {
		currMode = mode;
	}
}

int ProjectileSpawner::getShotMode()
{
	return currMode;
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
		float ang = rand() % 101 + 1;
		ang = ang / 100.0 * inacDispersion;
		float s = rand() % 100;
		float side = 1;

		if (s < 50)
			side = -1;

		rotateVector(shot, ang * side);
	}
}

int ProjectileSpawner::getNmodes()
{
	return nModes;
}