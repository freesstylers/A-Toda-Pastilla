#include "Components\Danio.h"
#include "Entity/Entity.h"
#include "Events/Event.h"
#include "Components/VidaEnemigos.h"
#include "Components/VidaPlayer.h"

Danio::Danio(json& args) : Component(args)
{

}

Danio::~Danio()
{

}

void Danio::update()
{

}

void Danio::init(json& j)
{
	if (!j["danio"].is_null()) danio_ = j["danio"];
	EventManager::getInstance()->RegisterListener(e_, "RIGIDBODY_COLLISION");
}

void Danio::OnCollision(Entity* other)
{
	if (other->getTag() == "Enemy") {
		other->getComponent<VidaEnemigos>("VidaEnemigos")->sumaVida(-danio_);
		e_->getComponent<VidaPlayer>("VidaPlayer")->sumaVida(-1);
		
	}
}