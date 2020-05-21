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

	void init(json& j) override;
	void update() override;

	int getScore();
	void addScore(int s);
	void pause();
	void unpause();
	bool isPaused();

	bool isBombActive();

	int getRecordScore();

	virtual bool ReceiveEvent(Event& event) override;

private:
	void registrarListeners();
	GameManager();
	static GameManager* instance;

	std::string nameFile = "Score";
	int recordScore_ = 0;
	int score_ = 0;
	bool paused_ = false;
	bool bombaEutanasica_ = false;
	//hacer un isActive apra la bomba eutanasica
};

#endif // !GAMEMANAGER_H
