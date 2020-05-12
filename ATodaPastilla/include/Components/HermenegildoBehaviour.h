#pragma once
#include "Entity\Component.h"

class ProjectileSpawner;

class HermenegildoBehaviour :public Component
{
public:
	HermenegildoBehaviour(json& args);
	~HermenegildoBehaviour() {};
	void init(json& j) override;
	void start() override;
	void update() override;

private:
	ProjectileSpawner* prSpawner;
	float timeSinceLastShot;
	float timeSinceLastAttack;
	float cadence;
	int shotsPerAttack;
	int shotsFired;
	float timeBetweenAttacks;
};

