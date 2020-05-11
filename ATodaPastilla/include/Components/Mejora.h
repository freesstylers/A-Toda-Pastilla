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
}; 
