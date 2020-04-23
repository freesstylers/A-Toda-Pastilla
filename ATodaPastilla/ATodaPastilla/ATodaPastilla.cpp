#include <iostream>
#include <stdexcept>
#define NOMINMAX

#include "windows.h"
#include "MotorCasaPaco.h"
#include "Entity/Factory.h"

#include "Components/MovimientoMando.h"
#include "Components/EntitySpawner.h"
#include "Components/DisparoWiterico.h"

#include "Scene/JsonFactoryParser.h"
#include "Components/Danio.h"
#include "Components/Vida.h"
#include "Components/ChangeSceneButtonComponent.h"
#include "Components/ExitButtonComponent.h"

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

class DisparoWitericoFactory : public BaseFactory {
public:
	Component* createComponent(json& args) override {
		return new DisparoWiterico(args);
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


void setupFactories()
{
	JsonFactoryParser* j = JsonFactoryParser::getInstance();

	j->addFactory("MovimientoMando", new MovimientoMandoFactory());
	j->addFactory("EntitySpawner", new EntitySpawnerFactory());
	j->addFactory("Danio", new DanioFactory());
	j->addFactory("Vida", new VidaFactory());
	j->addFactory("DisparoWiterico", new DisparoWitericoFactory());
	j->addFactory("ChangeSceneButtonComponent", new ChangeSceneButtonComponentFactory());
	j->addFactory("ExitButtonComponent", new ExitButtonComponentFactory());
}

#ifdef  _DEBUG
int main(int argc, char* argv[])
#else
#include <Windows.h>
int WINAPI
WinMain(HINSTANCE hinstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif
{

	try { MotorCasaPaco::setupInstance("Motor Casa Paco"); }
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

	motorCasaPaco->getGUI_Manager()->getInstance()->loadScheme("A_Toda_Pastilla.scheme");
	motorCasaPaco->getGUI_Manager()->getInstance()->loadScheme("GWEN.scheme");
	motorCasaPaco->getGUI_Manager()->getInstance()->setMouseCursor("A_Toda_Pastilla/Mouse_Arrow");
	motorCasaPaco->changeScene("Menu");

	motorCasaPaco->start();

	delete motorCasaPaco;

	return 0;
}