#pragma once
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Entity/Component.h"

class GameManager: public Component
{
public:
	~GameManager();

	static GameManager* getInstance();
	static void clean();

	int getScore();
	void addScore(int s);

private:
	GameManager();
	static GameManager* instance;

	int score_ = 0;

};

#endif // !GAMEMANAGER_H
