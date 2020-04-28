#pragma once
#include "ProjectileSpawner.h"
class DisparoWiterico : public ProjectileSpawner
{
public:
	DisparoWiterico(json& args);
	~DisparoWiterico() {};
	void init(json& args) override;
	void start() override;
	void update() override;
private:
	float timeSinceLastShot;
	float cadence;
};

