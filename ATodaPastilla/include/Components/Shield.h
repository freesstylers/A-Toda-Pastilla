#pragma once

#include "Entity/Component.h"
#include "Entity/Transform.h"
#include "Components/VidaPlayer.h"

class Shield :public Component
{
public:
	Shield(json& args);
	~Shield();
	void update() override;
	void init(json& j) override;
	bool getActivo() { return activo; };

private:
	bool activo = false;
	Transform* playerTrans;
	VidaPlayer* playerVida;
};
