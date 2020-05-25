#include "Components/EutanasiaTexto.h"
#include "Entity/Entity.h"
#include "MotorCasaPaco.h"
#include"Graphics/Mesh.h"
#include "Physics/RigidBody.h"
#include "Entity/Transform.h"
#include "Audio/AudioManager.h"
EutanasiaTexto::EutanasiaTexto(json& args) : Component(args)
{

}

EutanasiaTexto::~EutanasiaTexto()
{

}

void EutanasiaTexto::init(json& args)
{
	std::cout << "hola" << std::endl;
}

void EutanasiaTexto::start()
{
	EventManager::getInstance()->RegisterListener(this->getEntity(), "BombaImpacto");
	e_->getComponent<Mesh>("Mesh")->setEnabled(false);
}

bool EutanasiaTexto::ReceiveEvent(Event& event)
{
	if (event.type == "BombaImpacto")
	{
		bombazo = true;
		e_->getComponent<Mesh>("Mesh")->setEnabled(true);
		MotorCasaPaco::getInstance()->getAudioManager()->playMusic("assets/sound/ExplosionEutanasica.wav", 3, false);
	}
	return false;
}

void EutanasiaTexto::update()
{
	if (bombazo)
	{
		cooldown += MotorCasaPaco::getInstance()->DeltaTime();
		Vector3 size = e_->getComponent<Transform>("Transform")->getScale();
		size = Vector3(size.X + 0.1f,size.Y + 0.1f, size.Z +0.1f);
		e_->getComponent<Transform>("Transform")->setScale(size);
		if (cooldown >= 3.0f)
		{
			bombazo = false;
			cooldown = 0.0f;
			e_->getComponent<Transform>("Transform")->setScale(Vector3(6, 6, 6));
			e_->getComponent<Mesh>("Mesh")->setEnabled(false);
		}
	}
}