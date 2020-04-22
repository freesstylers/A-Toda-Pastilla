#include "Components\Danio.h"
#include "Entity/Entity.h"
#include "Events/Event.h"
#include "Components/Vida.h"

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
	EventManager::getInstance()->RegisterListener(getEntity(), EventType::RIGIDBODY_COLLISION);
}

bool Danio::ReceiveEvent(Event& event)
{
	switch (event.type)
	{
	case EventType::RIGIDBODY_COLLISION:
	{
		Entity* e1 = static_cast<RigidBodyCollisionEvent&>(event).obj1;
		Entity* e2 = static_cast<RigidBodyCollisionEvent&>(event).obj2;
		doDamage(e1, e2);
		break;
	}
	default:
		break;
	}
	return false;
}

void Danio::doDamage(Entity* e1, Entity* e2)
{
	Vida* v = nullptr;
	if (e_->getName() == e1->getName())
		v = e2->getComponent<Vida>("Vida");
	if (e_->getName() == e2->getName())
		v = e1->getComponent<Vida>("Vida");
	if(v != nullptr)
		v->sumaVida(-danio_);
}
