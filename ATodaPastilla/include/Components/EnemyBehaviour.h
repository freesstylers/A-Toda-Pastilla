#pragma once
#include "Entity\Component.h"
class EnemyBehaviour :public Component
{
public:
	EnemyBehaviour(json& args);
	void setSpawnPos(Vector3 spawnPos);
	void setEnemyIndx(int indx);
	virtual void OnDeath();
	virtual bool ReceiveEvent(Event& event) override;

protected:
	Vector3 spawnPosition;
	int spawnIndx;
};

