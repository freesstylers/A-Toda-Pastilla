#pragma once
#include"Components/EntitySpawner.h"

struct ShotInfo {
	Vector3 shotPos=Vector3(0,0,0);
	Vector3 shotDir=Vector3(0, 0, -1);
	int nBullets=0;
	float cadence=0;
	float bulletSpeed=0;
	float dispersionAngle=0;
	float inacDispersion=0;
	float inaccuracy=0;
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

private:
	void rotateVector(Vector3& vec, float angle);
	void calculateInaccuracy(Vector3& shot, float inaccuracy, float inacDispersion);
};

