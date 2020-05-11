#pragma once
#include "Entity/Component.h"

class Mejora : public Component
{
public:
	Mejora(json& args);
	~Mejora();

	virtual void OnCollision(Entity* ent) override;
	virtual void update() override;
	void init(json& j) override;

private:
	float rotation_ = 0.1;

	float sinusoidalMagnitude = 50.0;
	float sinusoidalFrequency = 2.0;

	int movVertical = 30;
}; 
