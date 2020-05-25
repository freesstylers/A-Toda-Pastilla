#pragma once
#ifndef VIDA_H
#define VIDA_H

#include "Entity\Component.h"

class Vida : public Component
{
public:
	Vida(json& args);
	~Vida();
	void start() override;
	void update() override;
	void init(json& j) override;
	int GetVida() {
		return vida_;
	}
	bool isDead() { return death_; };

	virtual void sumaVida(int valor);
protected:
	bool customDeath_;
	int vidaMax_ = 2;
	//int vidaInicial = 1;
	int vida_ = 1;
	int timeToLive_;
	float time_ = 0;
	bool timeD_ = false;
	bool death_ = false;

};

#endif // VIDA_H