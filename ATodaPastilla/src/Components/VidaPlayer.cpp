#include "Components/VidaPlayer.h"
#include "MotorCasaPaco.h"
#include "checkML.h"

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
	vida_ = 1;
}
void VidaPlayer::start()
{
	vida_ = 1;
}
void VidaPlayer::update()
{
	t_ += MotorCasaPaco::getInstance()->DeltaTime();
	//std::cout << t_ << "\n";
}

void VidaPlayer::sumaVida(int valor)
{
	if ((valor < 0 && t_ > invulnerabilityTime_) || valor > 0) {
		Vida::sumaVida(valor);
		if(valor < 0)
			t_ = 0;
	}
	if (vida_ <= 0) {
		//EventManager::getInstance()->RegisterListener(e_, "PlayerDeath");
		EventManager::getInstance()->EmitEvent("PlayerDeath");
	}
}