#pragma once
#include "ProjectileSpawner.h"
class DisparoWiterico : public ProjectileSpawner
{
public:
	DisparoWiterico(json& args);
	~DisparoWiterico() {};
	void init(json& j) override;
	void start() override;
	void update() override;
	bool ReceiveEvent(Event& event) override;

private:
	float timeSinceLastShot;

	Vector3 shotPos;
	Vector3 shotDir;
	int nBullets;
	float cadence;
	float bulletSpeed;
	float dispersionAngle;
	float inacDispersion;
	float inaccuracy;
};

