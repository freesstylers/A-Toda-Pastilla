#include "Components/GameManager.h"
#include "MotorCasaPaco.h"
#include "Components/EventsGame.h"
#include "Entity/Entity.h"
#include "Scene/SceneManager.h"
#include "GUI/GUI_Manager.h"
#include <iostream>
#include <fstream>
#include "Input/InputManager.h"

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

GameManager::GameManager(): Component("GameManager") 
{
	std::ifstream file(nameFile);
	//Comprueba que si existe el archivo
	if (file.good())
		file >> recordScore_;
	else //si no existe lo pone a 0
		recordScore_ = 0;
	file.close();
}

void GameManager::setEndGameLayout()
{
	GUI_Manager::getInstance()->changeText(GUI_Manager::getInstance()->getStaticText("endGame/Score"), "PUNTUACIÓN " + std::to_string(score_));
	GUI_Manager::getInstance()->changeText(GUI_Manager::getInstance()->getStaticText("endGame/Record"), "RECORD " + std::to_string(recordScore_));

	auto Function1 = std::bind(&GameManager::functionReplay, this, std::placeholders::_1);
	GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton("endGame/Replay"), Function1);

	auto Function2 = std::bind(&GameManager::functionMenu, this, std::placeholders::_1);
	GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton("endGame/Menu"), Function2);

	xPos[0] = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild("endGame/Replay").getCenterPointXAbsolute();
	yPos = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild("endGame/Replay").getCenterPointYAbsolute();
	xPos[1] = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild("endGame/Menu").getCenterPointXAbsolute();
}

bool GameManager::functionReplay(const CEGUI::EventArgs& e)
{
	SceneManager::getInstance()->changeScene(SceneManager::getInstance()->getCurrentScene()->getName());
	return true;
}

bool GameManager::functionMenu(const CEGUI::EventArgs& e)
{
	SceneManager::getInstance()->changeScene("Menu");
	return true;
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

	else if (dead && paused_)
	{
			if (MotorCasaPaco::getInstance()->getTimeDifference(currentTime) > delay)
			{
				//Mando y tal

				if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTX, true) < -0.7 || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_LEFT) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_A) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_LEFT))
				{
					if (menuPos == 0)
					{
						menuPos = 1;
					}
					else
					{
						menuPos = 0;
					}

					MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(xPos[menuPos], yPos);
					currentTime = MotorCasaPaco::getInstance()->getTime();
				}
				else if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTX, true) > 0.7 || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_RIGHT) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_D) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_RIGHT))
				{
					if (menuPos == 0)
					{
						menuPos = 1;
					}
					else
					{
						menuPos = 0;
					}

					MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(xPos[menuPos], yPos);
					currentTime = MotorCasaPaco::getInstance()->getTime();
				}
			}

			if (MotorCasaPaco::getInstance()->getInputManager()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_A) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_SPACE))
			{
				MotorCasaPaco::getInstance()->getInputManager()->injectLeftMouseButtonDown();
			}
			else
			{
				MotorCasaPaco::getInstance()->getInputManager()->injectLeftMouseButtonUp();
			}
	}
}

void GameManager::pausedUpdate()
{
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

	paused_ = !paused_;

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

		setEndGameLayout();

		GUI_Manager::getInstance()->setLayoutVisible(0, false);
		GUI_Manager::getInstance()->setLayoutVisible(GUI_Manager::getInstance()->getLayouts().size() - 1, true);
		GUI_Manager::getInstance()->showMouseCursor();

		pause();

		ingame_ = false;
		dead = true;
		currentTime = MotorCasaPaco::getInstance()->getTime();

		//Event evt = Event("Death");
		//EventManager::getInstance()->EmitEvent(evt);
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