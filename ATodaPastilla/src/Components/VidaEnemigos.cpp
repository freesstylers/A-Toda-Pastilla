
#include "Components/VidaEnemigos.h"
#include "Components/EventsGame.h"
#include "Entity/Entity.h"
#include "Entity/Transform.h"

VidaEnemigos::VidaEnemigos(json& args): Vida(args)
{

}

void VidaEnemigos::init(json& j)
{
	if (!j["puntos"].is_null())
		puntos_ = j["puntos"];
	Vida::init(j);

}

VidaEnemigos::~VidaEnemigos()
{

}

void VidaEnemigos::sumaVida(int valor)
{
	Vida::sumaVida(valor);
	EventManager::getInstance()->EmitEvent("Hit");
	if (vida_ <= 0 && !muerte_) {
		EventPuntuacion e(puntos_, e_->getTransform()->getWorldPosition());
		EventManager::getInstance()->EmitEvent(e);
		muerte_ = true;
	}
}