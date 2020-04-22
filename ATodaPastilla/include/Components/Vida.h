#pragma once
#ifndef VIDA_H
#define VIDA_H

#include "Entity\Component.h"

class Vida : public Component
{
public:
	Vida(json& args);
	~Vida();
	void update() override;
	void init(json& j) override;

	void sumaVida(int valor);
private:
	int vida_ = 1;
};

#endif // VIDA_H