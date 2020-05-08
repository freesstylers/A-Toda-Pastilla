#pragma once
#include "ProjectileSpawner.h"

struct ShotInfo {
	Vector3 shotPos = Vector3(0, 0, 0);
	Vector3 shotDir = Vector3(0, 0, -1);
	int nBullets = 0;
	float damagePerBullet = 0;
	float cadence = 0;
	float bulletSpeed = 0;
	float dispersionAngle = 0;
	float inacDispersion = 0;
	float inaccuracy = 0;
};
class DisparoWiterico : public ProjectileSpawner
{
public:
	DisparoWiterico(json& args);
	~DisparoWiterico() {};
	void init(json& j) override;
	void start() override;
	void update() override;

private:
	std::vector<ShotInfo>shotModes;
};

