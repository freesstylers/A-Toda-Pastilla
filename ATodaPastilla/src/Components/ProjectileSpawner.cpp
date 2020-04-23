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

void ProjectileSpawner::spawnProjectiles(Vector3 pos, Vector3 dir, float speed, int nbullets, float dispersionAngle, float inaccuracy, float inacDipsersion, std::string prefab)
{
	float iniAngle = 0;
	Vector3 Dir = dir;
	if (nbullets > 1) {
		iniAngle = dispersionAngle / 2;
		Dir.X = Dir.X * cos(iniAngle * M_PI / 180.0) + Dir.Z * sin(iniAngle * M_PI / 180.0);
		Dir.Z = Dir.Z * sin(iniAngle * M_PI / 180.0) + Dir.Z * cos(iniAngle * M_PI / 180.0);
	}
	float ang = dispersionAngle / nbullets;
	for (int i = 0; i < nbullets; i++) {
		Entity* prj = spawnEntity(pos, prefab);
		double rot=dir.Angle(dir, Dir)* 180.0/ M_PI;
		if (Dir.X > 0) rot *= -1;

		prj->getComponent<Transform>("Transform")->setRotation(Vector3(0, rot, 0));
		prj->getComponent<ProjectileBehaviour>("ProjectileBehaviour")->setDir(Dir);
		prj->getComponent<ProjectileBehaviour>("ProjectileBehaviour")->setSpeed(speed);
		Dir.X = Dir.X * cos(-ang * M_PI / 180.0) + Dir.Z * sin(-ang * M_PI / 180.0);
		Dir.Z = Dir.Z * sin(-ang * M_PI / 180.0) + Dir.Z * cos(-ang * M_PI / 180.0);
	}
}
