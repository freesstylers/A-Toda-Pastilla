#pragma once
#include "Mejora.h"

class MejoraEutanasia : public Mejora
{
public:
	MejoraEutanasia(json& args);
	~MejoraEutanasia();

	virtual void OnCollision(Entity* ent) override;
	virtual void update() override;
	void init(json& j) override;

private:

}; 
