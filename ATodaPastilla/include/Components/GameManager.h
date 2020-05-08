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
	void pause();
	void unpause();
	bool isPaused();

private:
	GameManager();
	static GameManager* instance;

	int score_ = 0;
	bool paused_ = false;
};

#endif // !GAMEMANAGER_H
