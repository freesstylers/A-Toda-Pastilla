#pragma once
#ifndef MOVIMIENTOMANDO_H
#define MOVIMIENTOMANDO_H

#include "Entity/Component.h"

class MovimientoMando : public Component
{
public:
	MovimientoMando(json& args);
	~MovimientoMando();
	void update() override;
	void init(json& j) override;

private:
	Vector3 insideBounds(Vector3 position);

	float zUP_;
	float zDOWN_;
	float xLEFT_;
	float xRIGHT_;
};
#endif // !MOVIMIENTOMANDO_H