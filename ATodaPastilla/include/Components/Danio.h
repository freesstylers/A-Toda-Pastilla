#pragma once
#ifndef DANIO_H
#define DANIO_H

#include "Entity/Component.h"

class Danio : public Component
{
public:
	Danio (json& args);
	~Danio ();
	void update() override;
	void init(json& j) override;
	bool ReceiveEvent(Event& event) override;

private:
	void doDamage(Entity* e1, Entity* e2);
	int danio_;
};


#endif // DANIO_H