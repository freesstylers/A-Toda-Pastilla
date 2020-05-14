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

#include "Scene/JsonFactoryParser.h"
#include "Components/ProjectileBehaviour.h"
#include "Components/Danio.h"
#include "Components/Vida.h"
#include "Components/ChangeSceneButtonComponent.h"
#include "Components/ExitButtonComponent.h"
#include "Components/GiroContinuo.h"
#include "Components/MenuMuestraPersonaje.h"

/*
#include "Components/ApplyGraphicChangesComponent.h"
#include "Components/ChangeFullScreenComponent.h"
#include "Components/ChangeVyncComponent.h"
#include "Components/FormatResolutionChangeComponent.h"
#include "Components/RevertGraphicChangesComponent.h"
#include "Components/RevertAdvancedGraphicChangesComponent.h"
#include "Components/ChangeGammaComponent.h"
#include "Components/ChangeGraphicSceneComponent.h"
#include "Components/ApplyAdvancedGraphicChangesComponent.h"
#include "Components/FSAAChangeComponent.h"
#include "Components/ShadowsChangeComponent.h"
*/


#include "Components/MainMenuInputComponent.h"
#include "Components/PauseMenuComponent.h"
#include "Components/OptionsMenuComponent.h"
#include "Components/PlayerInput.h"
#include "Components/GameManager.h"
#include "Components/SpawnerMejora.h"
#include "Components/MejoraDisparo.h"
#include "Components/MejoraVida.h"
#include "Components/MejoraEutanasia.h"

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

/*
class ChangeFullScreenComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new ChangeFullScreenComponent(args);
	};
};

class FormatResolutionChangeComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new FormatResolutionChangeComponent(args);
	};
};

class ApplyGraphicChangesComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new ApplyGraphicChangesComponent(args);
	};
};

class ChangeVSyncComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new ChangeVSyncComponent(args);
	};
};

class FSAAChangeComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new FSAAChangeComponent(args);
	};
};

class ShadowsChangeComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new ShadowsChangeComponent(args);
	};
};

class ApplyAdvancedGraphicChangesComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new ApplyAdvancedGraphicChangesComponent(args);
	};
};

class RevertGraphicChangesComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new RevertGraphicChangesComponent(args);
	};
};

class RevertAdvancedGraphicChangesComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new RevertAdvancedGraphicChangesComponent(args);
	};
};

class ChangeGammaComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new ChangeGammaComponent(args);
	};
};

class ChangeGraphicSceneComponentFactory : public BaseFactory
{
public:
	Component* createComponent(json& args) override
	{
		return new ChangeGraphicSceneComponent(args);
	};
};
*/

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
	j->addFactory("ChangeSceneButtonComponent", new ChangeSceneButtonComponentFactory());
	j->addFactory("ExitButtonComponent", new ExitButtonComponentFactory());
	j->addFactory("GiroContinuo", new GiroContinuoFactory());
	j->addFactory("MenuMuestraPersonaje", new MenuMuestraPersonajeFactory());
	j->addFactory("ProjectileBehaviour", new ProjectileBehaviourFactory());
	/*
	j->addFactory("ChangeFullScreenComponent", new ChangeFullScreenComponentFactory());
	j->addFactory("FormatResolutionChangeComponent", new FormatResolutionChangeComponentFactory());
	j->addFactory("ApplyGraphicChangesComponent", new ApplyGraphicChangesComponentFactory());
	j->addFactory("ChangeVSyncComponent", new ChangeVSyncComponentFactory());
	j->addFactory("FSAAChangeComponent", new FSAAChangeComponentFactory());
	j->addFactory("ShadowsChangeComponent", new ShadowsChangeComponentFactory());
	j->addFactory("ApplyAdvancedGraphicChangesComponent", new ApplyAdvancedGraphicChangesComponentFactory());
	j->addFactory("RevertGraphicChangesComponent", new RevertGraphicChangesComponentFactory());
	j->addFactory("RevertAdvancedGraphicChangesComponent", new RevertAdvancedGraphicChangesComponentFactory());
	j->addFactory("ChangeGammaComponent", new ChangeGammaComponentFactory());
	j->addFactory("ChangeGraphicSceneComponent", new ChangeGraphicSceneComponentFactory());*/
	j->addFactory("MainMenuInputComponent", new MainMenuInputComponentFactory());
	j->addFactory("PauseMenuComponent", new PauseMenuComponentFactory());
	j->addFactory("OptionsMenuComponent", new OptionsMenuComponentFactory());
	j->addFactory("PlayerInput", new PlayerInputFactory());
	j->addFactory("GameManager", new GameManagerFactory());
	j->addFactory("SpawnerMejora", new SpawnerMejoraFactory());
	j->addFactory("MejoraDisparo", new MejoraDisparoFactory());
	j->addFactory("MejoraVida", new MejoraVidaFactory());
	j->addFactory("MejoraEutanasia", new MejoraEutanasiaFactory());
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

	delete motorCasaPaco;

	return 0;
}