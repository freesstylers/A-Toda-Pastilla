#pragma once
#include "EnemyBehaviour.h"

class ProjectileSpawner;

class HermenegildoBehaviour :public EnemyBehaviour
{
public:
	HermenegildoBehaviour(json& args);
	~HermenegildoBehaviour() {};
	void init(json& j) override;
	void start() override;
	void update() override;
	void OnCollision(Entity* other) override;
	void OnDeath() override;

private:
	std::string deathSound;
	std::string hitSound;
	ProjectileSpawner* prSpawner;
	float timeSinceLastShot;
	float timeSinceLastAttack;
	float cadence;
	float damage;
	float speed;
	int shotsPerAttack;
	int shotsFired;
	float timeBetweenAttacks;
	float dyingTime;
	float timeToDie;
	
};

