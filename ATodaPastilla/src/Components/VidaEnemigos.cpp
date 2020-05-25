
#include "Components/VidaEnemigos.h"
#include "Components/EventsGame.h"

VidaEnemigos::VidaEnemigos(json& args): Vida(args)
{

}

void VidaEnemigos::init(json& j)
{
	if (!j["puntos"].is_null())
		puntos_ = j["puntos"]/2;
	Vida::init(j);

}

VidaEnemigos::~VidaEnemigos()
{

}

void VidaEnemigos::sumaVida(int valor)
{
	Vida::sumaVida(valor);
	if (vida_ <= 0 && !muerte_) {
		//EventManager::getInstance()->RegisterListener(e_, "PlayerDeath");
		EventPuntuacion e(puntos_);
		EventManager::getInstance()->EmitEvent(e);
		muerte_ = true;
	}
}