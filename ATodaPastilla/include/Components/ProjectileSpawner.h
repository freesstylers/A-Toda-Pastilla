#pragma once
#include"Components/EntitySpawner.h"
class ProjectileSpawner :public EntitySpawner
{
public:
	ProjectileSpawner(json& args);
	~ProjectileSpawner() {};
	void init(json& j) override;
	void update() override;
	virtual void spawnProjectiles(Vector3 pos = Vector3(0, 0, 0), Vector3 dir = Vector3(0, 0, 0), float speed=0, int nbullets=1, float dispersionAngle=0, float inaccuracy=0, float inacDipsersion=0,  std::string prefab = "");
};

