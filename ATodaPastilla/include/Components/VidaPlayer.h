#pragma once
#ifndef VIDAPLAYER_H
#define VIDAPLAYER_H

#include "Vida.h"

class VidaPlayer: public Vida
{
public:
	VidaPlayer(json& args);
	~VidaPlayer();
	void init(json& j) override;

	void update() override;

	virtual void sumaVida(int valor);

private:
	int invulnerabilityTime_ = 1;
	float t_ = 0.0f;
};

#endif // VIDA_PLAYER_H
