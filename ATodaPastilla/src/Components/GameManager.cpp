#include "Components/GameManager.h"
#include "MotorCasaPaco.h"
#include "Components/EventsGame.h"
#include "Entity/Entity.h"

GameManager* GameManager::instance = 0;

GameManager::~GameManager()
{
}

//Registro del gameManager de todo lo que tenga que escuchar
void GameManager::registrarListeners()
{
	EventManager::getInstance()->RegisterListener(e_, "PlayerDeath");
	EventManager::getInstance()->RegisterListener(e_, "EnemyDeath");
}

GameManager::GameManager(): Component("GameManager") {
	

}

GameManager* GameManager::getInstance()
{
	if (instance == nullptr) {
		instance = new GameManager();
	}

	return instance;
}


void GameManager::clean()
{
	delete instance;
}

void GameManager::init(json& j)
{
	EventManager::getInstance()->UnregisterListenerForAll(e_);
	registrarListeners();
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

bool GameManager::ReceiveEvent(Event& event)
{
	if (event.type == "PlayerDeath") {
		//Tiene que cambiarse aqui la escena al menu
		//EventManager::getInstance()->EmitEvent("finNivel");
	}
	else if (event.type == "EnemyDeath") {
		score_ += static_cast<EventPuntuacion&>(event).puntuacion_;
	}
	return false;
}
