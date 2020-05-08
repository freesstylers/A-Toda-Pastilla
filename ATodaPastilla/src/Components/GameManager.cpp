#include "Components/GameManager.h"
#include "MotorCasaPaco.h"

GameManager* GameManager::instance = 0;

GameManager::~GameManager()
{
}

GameManager::GameManager(): Component("GameManager") {

}

GameManager* GameManager::getInstance()
{
	if (instance == nullptr)
		instance = new GameManager();

	return instance;
}


void GameManager::clean()
{
	delete instance;
}

int GameManager::getScore()
{
	return score_;
}

void GameManager::addScore(int s)
{
	score_ += s;
}

void GameManager::pause()
{
	MotorCasaPaco::getInstance()->pause();

	BoolEvent e = BoolEvent("PAUSE", MotorCasaPaco::getInstance()->isPaused());
	EventManager::getInstance()->EmitEvent(e);
}

bool GameManager::isPaused()
{
	return paused_;
}
