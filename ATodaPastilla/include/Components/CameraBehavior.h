#pragma once

#ifndef CAMERA_BEHAVIOR_H
#define CAMERA_BEHAVIOR_H

#include "Entity/Component.h"

class CameraBehavior : public Component
{
public:
	CameraBehavior(json& args);
	~CameraBehavior();
	void init(json& j) override;
	void update() override;

	virtual bool ReceiveEvent(Event& event) override;

private:
	void vibrar();
	float ticks = 0;

	float iniX_ = 0;
	bool start_ = false;

	int n = 0;

	std::vector<float> x_;
	float t_ = 0;
};


#endif // !CAMERA_BEHAVIOR_H
