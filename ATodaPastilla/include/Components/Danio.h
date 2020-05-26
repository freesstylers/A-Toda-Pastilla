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

	void OnCollision(Entity* other) override;

private:
	int danio_;
};


#endif // DANIO_H