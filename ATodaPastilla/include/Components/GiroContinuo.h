#pragma once
#ifndef GIROCONTINUO_H
#define GIROCONTINUO_H

#include "Entity/Component.h"

class GiroContinuo : public Component
{
public:
	GiroContinuo(json& args);
	~GiroContinuo();
	void update() override;
	void init(json& j) override;

private:
	float aRotation_ = 0;
	float rotation_ = 0.1;
};

#endif // !GIROCONTINUO_H
