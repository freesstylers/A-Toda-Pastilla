#include "Components\Vida.h"
#include "Entity/Entity.h"
#include "Events/Event.h"
#include <iostream>

Vida::Vida(json& args): Component(args)
{

}

Vida::~Vida()
{
	Component::~Component();
}

void Vida::update()
{
	std::cout << e_->getName() << ": " << vida_ << " \n";
}

void Vida::init(json& j)
{
	if (!j["vida"].is_null()) vida_ = j["vida"];
	
}

void Vida::sumaVida(int valor)
{
	vida_ += valor;
	//if (vida_ <= 0)
		//delete e_; //Sacar de la escena
}
