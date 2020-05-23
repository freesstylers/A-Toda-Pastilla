#pragma once

#ifndef VIDAENEMIGOS_H
#define VIDAENEMIGOS_H

#include "Vida.h"

class VidaEnemigos: public Vida
{
public:
	VidaEnemigos(json& args);
	virtual void init(json& j) override;
	~VidaEnemigos();

	virtual void sumaVida(int valor);

private:
	bool muerte_ = false;
	int puntos_ = 0;
};

#endif // !VIDAENEMIGOS_H
