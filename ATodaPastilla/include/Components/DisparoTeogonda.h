#pragma once
#include "ProjectileSpawner.h"

struct TeogondaShotInfo {
	Vector3 shotPos = Vector3(0, 0, 0);
	Vector3 shotDir = Vector3(0, 0, -1);
	float chargeTime;
	int chargeLevels;
	
	std::vector<int> nBullets;
	std::vector<float> bulletSpeed;
	std::vector<float> dispersionAngle;
	std::vector<float> inacDispersion;
	std::vector<float> inaccuracy;
	std::vector<float> burstCadence;
	std::vector<int> burstShots;
};
class DisparoTeogonda : public ProjectileSpawner
{
public:
	DisparoTeogonda(json& args);
	~DisparoTeogonda() {};
	void init(json& j) override;
	void start() override;
	void update() override;
	bool ReceiveEvent(Event& event) override;

private:
	std::vector<TeogondaShotInfo> shotModes;
	float timeCharged;
	int burstShotsFired;
	int currChargeLevel;
	void chargeShot();
	void fireBurst();

};

