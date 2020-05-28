#include "Components/MainMenuInputComponent.h"
#include "MotorCasaPaco.h"
#include "Audio/AudioManager.h"
#include "Input/InputManager.h"
#include "Components/GameManager.h"
#include "checkML.h"

MainMenuInputComponent::MainMenuInputComponent(json& args): Component(args)
{

}

MainMenuInputComponent::~MainMenuInputComponent()
{
	//EventManager::getInstance()->UnregisterListenerForAll(this);
	//Component::~Component();
}

bool MainMenuInputComponent::functionPlay(const CEGUI::EventArgs& e)
{
	Event evt = Event("Ingame");
	EventManager::getInstance()->EmitEvent(evt);

	MotorCasaPaco::getInstance()->changeScene(sceneToLoad);
	AudioManager::getInstance()->playMusic("assets/sound/buttonSound.mp3", 2, false);
	MotorCasaPaco::getInstance()->getGUI_Manager()->getInstance()->hideMouseCursor();
	MotorCasaPaco::getInstance()->getAudioManager()->stopChannel(0);
	return true;
}

bool MainMenuInputComponent::ReceiveEvent(Event& event)
{
	if (event.type == "Witerico")
	{
		sceneToLoad = "ATodaPastilla_Witerico";
	}

	else if (event.type == "Teodegonda")
	{
		sceneToLoad = "ATodaPastilla_Teodegonda";
	}

	return false;
}

void MainMenuInputComponent::update()
{
	if (MotorCasaPaco::getInstance()->getTimeDifference(currentTime) > delay)
	{
		if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTX, true) < -0.7 || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_LEFT) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_A) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_LEFT))
		{
			if (currenPos > 0)
				currenPos--;
			else
				currenPos = tam - 1;

			MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsX[currenPos], positionsY[currenPos]);
			currentTime = MotorCasaPaco::getInstance()->getTime();
		}
		else if (InputManager::getInstance()->GameControllerGetAxisMovement(GameControllerAxis::CONTROLLER_AXIS_LEFTX, true) > 0.7 || InputManager::getInstance()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_DPAD_RIGHT) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_D) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_RIGHT))
		{
			if (currenPos < (tam - 1))
				currenPos++;
			else
				currenPos = 0;

			MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsX[currenPos], positionsY[currenPos]);
			currentTime = MotorCasaPaco::getInstance()->getTime();
		}
	}

		//Boton A
		if (MotorCasaPaco::getInstance()->getInputManager()->GameControllerIsButtonDown(GameControllerButton::CONTROLLER_BUTTON_A) || InputManager::getInstance()->IsKeyDown(Scancode::SCANCODE_SPACE))
		{
			MotorCasaPaco::getInstance()->getInputManager()->injectLeftMouseButtonDown();
		}
		else
		{
			MotorCasaPaco::getInstance()->getInputManager()->injectLeftMouseButtonUp();
		}
	//}
}

void MainMenuInputComponent::init(json& j)
{
	if (!j["buttons"].is_null() && j["buttons"].is_array() && !j["delay"].is_null() && !j["playButton"].is_null())
	{
		std::vector<std::string> vec = j["buttons"];
		
		int count = 0;
		
		for (std::string name : vec) {

			float i = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getCenterPointXAbsolute();
			float j = MotorCasaPaco::getInstance()->getGUI_Manager()->getRoot()->getChild(name).getCenterPointYAbsolute();
			
			positionsX.push_back(i);
			positionsY.push_back(j);

			count++;
		}

		delay = j["delay"];
		currentTime = MotorCasaPaco::getInstance()->getTime();

		auto helperFunction = std::bind(&MainMenuInputComponent::functionPlay, this, std::placeholders::_1);
		GUI_Manager::getInstance()->setEvents(GUI_Manager::getInstance()->getPushButton(j["playButton"]), helperFunction);

		tam = count;
		currenPos = tam / 2;
		
		std::cout << tam << "\n";
		//posX = MotorCasaPaco::getInstance()->getScreenWidth() / 2;
		//posY = MotorCasaPaco::getInstance()->getScreenHeight() / 2;
		GUI_Manager::getInstance()->changeText(GUI_Manager::getInstance()->getStaticText("MainMenu/Score"), std::to_string(GameManager::getInstance()->getRecordScore()));

		MotorCasaPaco::getInstance()->getGUI_Manager()->injectPosition(positionsX[currenPos], positionsY[currenPos]);

		EventManager::getInstance()->RegisterListener(this, "Witerico");
		EventManager::getInstance()->RegisterListener(this, "Teodegonda");
	}
}
