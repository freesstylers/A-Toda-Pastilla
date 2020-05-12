#pragma once
#include "Mejora.h"

class MejoraDisparo : public Mejora
{
public:
	MejoraDisparo(json& args);
	~MejoraDisparo();

	virtual void OnCollision(Entity* ent) override;
	virtual void update() override;
	void init(json& j) override;

private:

}; 
