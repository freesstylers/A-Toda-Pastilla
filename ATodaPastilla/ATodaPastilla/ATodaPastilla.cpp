#include <iostream>
#include <stdexcept>
#define NOMINMAX

#include "windows.h"
#include "MotorCasaPaco.h"
#include "Entity/Factory.h"

#include "Components/MovimientoMando.h"
#include "Components/EntitySpawner.h"
#include "Components/ProjectileSpawner.h"
#include "Components/EnemySpawner.h"
#include "Components/DisparoWiterico.h"
#include "Components/DisparoTeodegonda.h"
#include "Components/RicibergaBehaviour.h"
#include "Components/HermenegildoBehaviour.h"
#include "Components/CanutoBehaviour.h"

#include "Scene/JsonFactoryParser.h"
#include "Components/ProjectileBehaviour.h"
#include "Components/Danio.h"
#include "Components/VidaPlayer.h"
#include "Components/VidaEnemigos.h"
#include "Components/ChangeSceneButtonComponent.h"
#include "Components/ExitButtonComponent.h"
#include "Components/GiroContinuo.h"
#include "Components/MenuMuestraPersonaje.h"

#include "Components/MainMenuInputComponent.h"
#include "Components/PauseMenuComponent.h"
#include "Components/OptionsMenuComponent.h"
#include "Components/PlayerInput.h"
#include "Components/GameManager.h"
#include "Components/SpawnerMejora.h"
#include "Components/MejoraDisparo.h"
#include "Components/MejoraVida.h"
#include "Components/MejoraEutanasia.h"
#include "Components/musicManager.h"
#include "Components/EutanasiaTexto.h"
#include "Components/Shield.h"

MotorCasaPaco* motorCasaPaco;

class MovimientoMandoFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new MovimientoMando(args);
	};
};

class EntitySpawnerFactory : public BaseFactory {
public: 
	Component* createComponent(json& args) override {
		return new EntitySpawner(args);
	}
};

class ProjectileSpawnerFactory : public BaseFactory{
public:
	Component * createComponent(json & args) override {
		return new ProjectileSpawner(args);
	}
};

class EnemySpawnerFactory : public BaseFactory {
public: 
	Component* createComponent(json& args) override {
		return new EnemySpawner(args);
	}
};

class DisparoWitericoFactory : public BaseFactory {
public:
	Component* createComponent(json& args) override {
		return new DisparoWiterico(args);
	}
};

class DisparoTeodegondaFactory : public BaseFactory {
public:
	Component* createComponent(json& args) override {
		return new DisparoTeodegonda(args);
	}
};

class RicibergaBehaviourFactory : public BaseFactory {
public:
	Component* createComponent(json& args) override {
		return new RicibergaBehaviour(args);
	}
};

class HermenegildoBehaviourFactory : public BaseFactory {
public:
	Component* createComponent(json& args) override {
		return new HermenegildoBehaviour(args);
	}
};

class CanutoBehaviourFactory : public BaseFactory {
public:
	Component* createComponent(json& args) override {
		return new CanutoBehaviour(args);
	}
};

class ProjectileBehaviourFactory : public BaseFactory {
public:
	Component* createComponent(json& args) override {
		return new ProjectileBehaviour(args);
	}
};

class DanioFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new Danio(args);
	};
};

class VidaFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new Vida(args);
	};
};

class ChangeSceneButtonComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new ChangeSceneButtonComponent(args);
	};
};

class ExitButtonComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new ExitButtonComponent(args);
	};
};

class GiroContinuoFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new GiroContinuo(args);
	};
};

class MenuMuestraPersonajeFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new MenuMuestraPersonaje(args);
	};
};

class MainMenuInputComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new MainMenuInputComponent(args);
	};
};

class PauseMenuComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new PauseMenuComponent(args);
	};
};

class OptionsMenuComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new OptionsMenuComponent(args);
	};
};

class PlayerInputFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new PlayerInput(args);
	};
};

class GameManagerFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return (Component*)GameManager::getInstance();
	};
};

class SpawnerMejoraFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new SpawnerMejora(args);
	};
};

class MejoraDisparoFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new MejoraDisparo(args);
	};
};

class MejoraVidaFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new MejoraVida(args);
	};
};

class MejoraEutanasiaFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new MejoraEutanasia(args);
	};
};

class VidaPlayerFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new VidaPlayer(args);
	};
};

class VidaEnemigosFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new VidaEnemigos(args);
	};
};

class MusicManagerFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new MusicManager(args);
	};
};



class ShieldFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new Shield(args);
	}
};

class EutanasiaTextoFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new EutanasiaTexto(args);
	}
};

void setupFactories()
{
	JsonFactoryParser* j = JsonFactoryParser::getInstance();

	j->addFactory("MovimientoMando", new MovimientoMandoFactory());
	j->addFactory("EntitySpawner", new EntitySpawnerFactory());
	j->addFactory("ProjectileSpawner", new ProjectileSpawnerFactory());
	j->addFactory("EnemySpawner", new EnemySpawnerFactory());
	j->addFactory("Danio", new DanioFactory());
	j->addFactory("Vida", new VidaFactory());
	j->addFactory("DisparoWiterico", new DisparoWitericoFactory());
	j->addFactory("DisparoTeodegonda", new DisparoTeodegondaFactory());
	j->addFactory("RicibergaBehaviour", new RicibergaBehaviourFactory());
	j->addFactory("HermenegildoBehaviour", new HermenegildoBehaviourFactory());
	j->addFactory("CanutoBehaviour", new CanutoBehaviourFactory());
	j->addFactory("ChangeSceneButtonComponent", new ChangeSceneButtonComponentFactory());
	j->addFactory("ExitButtonComponent", new ExitButtonComponentFactory());
	j->addFactory("GiroContinuo", new GiroContinuoFactory());
	j->addFactory("MenuMuestraPersonaje", new MenuMuestraPersonajeFactory());
	j->addFactory("ProjectileBehaviour", new ProjectileBehaviourFactory());
	j->addFactory("MainMenuInputComponent", new MainMenuInputComponentFactory());
	j->addFactory("PauseMenuComponent", new PauseMenuComponentFactory());
	j->addFactory("OptionsMenuComponent", new OptionsMenuComponentFactory());
	j->addFactory("PlayerInput", new PlayerInputFactory());
	j->addFactory("GameManager", new GameManagerFactory());
	j->addFactory("SpawnerMejora", new SpawnerMejoraFactory());
	j->addFactory("MejoraDisparo", new MejoraDisparoFactory());
	j->addFactory("MejoraVida", new MejoraVidaFactory());
	j->addFactory("MejoraEutanasia", new MejoraEutanasiaFactory());
	j->addFactory("VidaPlayer", new VidaPlayerFactory());
	j->addFactory("VidaEnemigos", new VidaEnemigosFactory());
	j->addFactory("MusicManager", new MusicManagerFactory());
	j->addFactory("EutanasiaTexto", new EutanasiaTextoFactory());
	j->addFactory("Shield", new ShieldFactory());
}

#ifdef  _DEBUG
int main(int argc, char* argv[])
#else
#include <Windows.h>
int WINAPI
WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif
{

	try { MotorCasaPaco::setupInstance("A Toda Pastilla"); }
	catch (const std::exception& e)
	{
		throw std::runtime_error("Motor Casa Paco init fail \n" + std::string(e.what()) + "\n");	return 0;
	}

	motorCasaPaco = MotorCasaPaco::getInstance();

	try
	{
		motorCasaPaco->init();
		setupFactories();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << "\n";
		delete motorCasaPaco;
		return 0;
	}

	MotorCasaPaco::getInstance()->getGUI_Manager()->loadScheme("A_Toda_Pastilla.scheme");
	MotorCasaPaco::getInstance()->getGUI_Manager()->setMouseCursor("A_Toda_Pastilla/Mouse_Arrow");

	motorCasaPaco->start("Menu");

	GameManager::getInstance()->clean();
	delete motorCasaPaco;

	return 0;
}