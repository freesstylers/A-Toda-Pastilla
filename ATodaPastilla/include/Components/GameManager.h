#pragma once
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "Entity/Component.h"
#include "GUI/GUI_Manager.h"

class GameManager: public Component
{
public:
	~GameManager();

	static GameManager* getInstance();
	static void clean();

	void init(json& j) override;
	void update() override;
	void pausedUpdate() override;

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
	void setEndGameLayout();
	bool functionReplay (const CEGUI::EventArgs& e);
	bool functionMenu (const CEGUI::EventArgs& e);

	std::string nameFile = "Score";
	int recordScore_ = 0;
	int score_ = 0;
	bool paused_ = false;
	bool ingame_ = false;
	bool bombaEutanasica_ = false;

	//Cosas de menu de fin de partida
	bool dead = false;
	float currentTime;
	float delay = 0.15;
	int menuPos = 0;
	float xPos[2] = {};
	float yPos;
	//hacer un isActive apra la bomba eutanasica
};

#endif // !GAMEMANAGER_H
