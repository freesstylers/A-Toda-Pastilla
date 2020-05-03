#pragma once
#include"Components/EntitySpawner.h"

struct ShotInfo {
	Vector3 shotPos;
	Vector3 shotDir;
	int nBullets;
	float cadence;
	float bulletSpeed;
	float dispersionAngle;
	float inacDispersion;
	float inaccuracy;
};
class ProjectileSpawner :public EntitySpawner
{
public:
	ProjectileSpawner(json& args);
	~ProjectileSpawner() {};
	void init(json& j) override;
	void update() override;
	virtual void spawnProjectiles(Vector3 pos = Vector3(0, 0, 0), Vector3 dir = Vector3(0, 0, 0), float speed=0, int nbullets=1, float dispersionAngle=0, float inaccuracy=0, float inacDipsersion=0,  std::string prefab = "");
	virtual std::vector<ShotInfo> getShotModes();
	virtual ShotInfo getCurrentShotMode();
	virtual void setShotMode(int mode);

protected:
	float timeSinceLastShot;
	std::vector<ShotInfo>shotModes;
	int currMode;
	int nModes;
};

