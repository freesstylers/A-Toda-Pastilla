#pragma once
#include "ProjectileSpawner.h"

struct TeogondaShotInfo {
	float chargeTime;
	int chargeLevels;
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
	std::vector<TeogondaShotInfo> teoModes;
	float timeCharged;
	int burstShotsFired;
	int currChargeLevel;
	void chargeShot();
	void fireBurst();

};

