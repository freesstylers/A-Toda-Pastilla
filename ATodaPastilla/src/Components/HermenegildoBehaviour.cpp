#include "Components\HermenegildoBehaviour.h"
#include "Entity/Entity.h"
#include "Components/ProjectileSpawner.h"
#include "MotorCasaPaco.h"

HermenegildoBehaviour::HermenegildoBehaviour(json& args):Component(args)
{

}

void HermenegildoBehaviour::init(json& j)
{
	if (!j["cadence"].is_null()) {
		cadence =j["cadence"];
	}
	if (!j["shotsPerAttack"].is_null()) {
		shotsPerAttack = j["shotsPerAttack"];
	}
	if (!j["timeBetweenAttacks"].is_null()) {
		timeBetweenAttacks = j["timeBetweenAttacks"];
	}
}

void HermenegildoBehaviour::start()
{
	prSpawner = e_->getComponent<ProjectileSpawner>("ProjectileSpawner");

	shotsFired = 0;
	timeSinceLastAttack = timeBetweenAttacks;
	timeSinceLastShot = cadence;
}

void HermenegildoBehaviour::update()
{
	if (prSpawner != nullptr) {
		if (timeSinceLastAttack >= timeBetweenAttacks) {
			if (shotsFired < shotsPerAttack) {
				if (timeSinceLastShot >= cadence) {
					prSpawner->spawnProjectiles(Vector3(-10, 0, 0), Vector3(0, 0, 1), 100, 1, 10);

					prSpawner->spawnProjectiles(Vector3(10, 0, 0), Vector3(0, 0, 1), 100, 1, 10);

					shotsFired++;
					timeSinceLastShot = 0;
				}
				timeSinceLastShot += MotorCasaPaco::getInstance()->DeltaTime();
			}
			else {
				timeSinceLastAttack = 0;
				shotsFired = 0;
			}
		}
		else {
			timeSinceLastAttack += MotorCasaPaco::getInstance()->DeltaTime();
		}
	}
}

