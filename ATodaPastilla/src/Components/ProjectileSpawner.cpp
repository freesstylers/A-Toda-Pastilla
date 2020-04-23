#include "Components/ProjectileSpawner.h"
#include "Entity/Entity.h"
#include "Physics/RigidBody.h"
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
		Dir.X = Dir.X * cos(iniAngle) + Dir.Z * sin(iniAngle);
		Dir.Z = Dir.Z * sin(iniAngle) + Dir.Z * cos(iniAngle);
	}
	float ang = dispersionAngle / nbullets;
	for (int i = 0; i < nbullets; i++) {
		Entity* prj = spawnEntity(pos, prefab);
		prj->getComponent<RigidBody>("RigidBody")->applyForce(LINEAR_VELOCITY, Dir * speed * MotorCasaPaco::getInstance()->DeltaTime());
		Dir.X = Dir.X * cos(-ang) + Dir.Z * sin(-ang);
		Dir.Z = Dir.Z * sin(-ang) + Dir.Z * cos(-ang);
	}
}
