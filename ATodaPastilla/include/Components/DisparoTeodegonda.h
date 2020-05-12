#pragma once
#include "ProjectileSpawner.h"

struct TeodegondaShotInfo {
	Vector3 shotPos = Vector3(0, 0, 0);
	Vector3 shotDir = Vector3(0, 0, -1);
	float chargeTime;
	int chargeLevels;
	std::string maximumChargeSound="";

	std::vector<std::string> chargeSound;
	std::vector<std::string> shotSound;
	std::vector<int> nBullets;
	std::vector<float> damagePerBullet;
	std::vector<float> bulletSpeed;
	std::vector<float> dispersionAngle;
	std::vector<float> inacDispersion;
	std::vector<float> inaccuracy;
	std::vector<float> burstCadence;
	std::vector<int> burstShots;
};
class DisparoTeodegonda : public ProjectileSpawner
{
public:
	DisparoTeodegonda(json& args);
	~DisparoTeodegonda() {};
	void init(json& j) override;
	void start() override;
	void update() override;
	bool ReceiveEvent(Event& event) override;

private:
	void chargeShot();
	void fireBurst();

	std::vector<TeodegondaShotInfo> shotModes;
	float timeCharged;
	int burstShotsFired;
	int currChargeLevel;

};

