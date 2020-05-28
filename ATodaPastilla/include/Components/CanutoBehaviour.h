#pragma once
#include "EnemyBehaviour.h"

class ProjectileSpawner;

class CanutoBehaviour :public EnemyBehaviour
{
public:
	CanutoBehaviour(json& args);
	~CanutoBehaviour() {};
	void init(json& j) override;
	void start() override;
	void update() override;
	void OnCollision(Entity* other) override;
	void OnDeath() override;

private:
	std::string deathSound;
	std::string hitSound;
	ProjectileSpawner* prSpawner;
	float bottom;
	float timeSinceLastAttack;
	float damage;
	float speed;
	float bulletSpeed;
	float timeBetweenAttacks;
	float minTimeBtwAtk;
	float maxTimeBtwAtk;
	float dyingTime;
	float timeToDie;
	bool awayFromSpawn;
};

