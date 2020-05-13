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
	bool ReceiveEvent(Event& event) override;
	void OnCollision(Entity* other) override;

private:
	std::string deathSound;
	std::string hitSound;
	ProjectileSpawner* prSpawner;
	float timeSinceLastShot;
	float timeSinceLastAttack;
	float cadence;
	int shotsPerAttack;
	int shotsFired;
	float timeBetweenAttacks;
	float dyingTime;
	float timeToDie;
	
};

