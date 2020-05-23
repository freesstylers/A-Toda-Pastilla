#include "Components/GameManager.h"
#include "MotorCasaPaco.h"
#include "Components/EventsGame.h"
#include "Entity/Entity.h"
#include "Scene/SceneManager.h"
#include "GUI/GUI_Manager.h"
#include <iostream>
#include <fstream>

GameManager* GameManager::instance = 0;

GameManager::~GameManager()
{
	//Guardado del mejor score
	std::ofstream file(nameFile);

	file << recordScore_;

	file.close();
}

//Registro del gameManager de todo lo que tenga que escuchar
void GameManager::registrarListeners()
{
	EventManager::getInstance()->RegisterListener(e_, "PlayerDeath");
	EventManager::getInstance()->RegisterListener(e_, "EnemyDeath");
	EventManager::getInstance()->RegisterListener(e_, "BombaUp");
	EventManager::getInstance()->RegisterListener(e_, "BombaDown");
	EventManager::getInstance()->RegisterListener(e_, "Ingame");
	EventManager::getInstance()->RegisterListener(e_, "Menu");
}

GameManager::GameManager(): Component("GameManager") {
	std::ifstream file(nameFile);
	//Comprueba que si existe el archivo
	if (file.good())
		file >> recordScore_;
	else //si no existe lo pone a 0
		recordScore_ = 0;
	file.close();
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
	bombaEutanasica_ = false;
	score_ = 0;
}

void GameManager::update()
{
	//Update Score
	if (ingame_ && !paused_)
	{
		GUI_Manager::getInstance()->changeText(GUI_Manager::getInstance()->getStaticText("Ingame/CurrentScore"), std::to_string(score_));
		GUI_Manager::getInstance()->changeText(GUI_Manager::getInstance()->getStaticText("Ingame/Record"), std::to_string(recordScore_));
	}
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

bool GameManager::isBombActive()
{
	return bombaEutanasica_;
}

int GameManager::getRecordScore()
{
	return recordScore_;
}

bool GameManager::ReceiveEvent(Event& event)
{
	//Mensaje de muerte del jugador
	if (event.type == "PlayerDeath") {
		if (recordScore_ < score_)
			recordScore_ = score_;
		SceneManager::getInstance()->changeScene("Menu");
		ingame_ = false;
	}
	//Mensaje de muerte de un enemigo, da igual que sea un boss o no
	else if (event.type == "EnemyDeath") {
		score_ += static_cast<EventPuntuacion&>(event).puntuacion_;
	}
	//Activa a desactiva en funcion de si tiene o no la bomba
	else if (event.type == "BombaUp") {
		bombaEutanasica_ = true;
	}
	else if (event.type == "BombaDown") {
		bombaEutanasica_ = false;
	}
	else if (event.type == "Ingame")
	{
		ingame_ = true;
	}
	else if (event.type == "Menu")
	{
		ingame_ = false;
	}
	return false;
}