#pragma once
#include "Mejora.h"

class MejoraVida : public Mejora
{
public:
	MejoraVida(json& args);
	~MejoraVida();

	virtual void OnCollision(Entity* ent) override;
	virtual void update() override;
	void init(json& j) override;

private:

}; 
