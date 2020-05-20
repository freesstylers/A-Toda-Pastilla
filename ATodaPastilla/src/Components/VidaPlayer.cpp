#include "Components/VidaPlayer.h"
#include "MotorCasaPaco.h"

VidaPlayer::VidaPlayer(json& args) : Vida(args)
{

}

VidaPlayer::~VidaPlayer()
{
}

void VidaPlayer::init(json& j)
{
	if (!j["invulnerabilityTime"].is_null())
		invulnerabilityTime_ = j["invulnerabilityTime"];
	Vida::init(j);
}

void VidaPlayer::update()
{
	t_ += MotorCasaPaco::getInstance()->DeltaTime();
}

void VidaPlayer::sumaVida(int valor)
{
	if ((valor > 0 && t_ > invulnerabilityTime_) || valor < 0) {
		Vida::sumaVida(valor);
		if(valor > 0)
			t_ = 0;
	}
	if (vida_ <= 0) {
		//EventManager::getInstance()->RegisterListener(e_, "PlayerDeath");
		EventManager::getInstance()->EmitEvent("PlayerDeath");
	}
}