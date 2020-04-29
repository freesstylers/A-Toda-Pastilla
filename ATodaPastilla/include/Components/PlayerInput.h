#pragma once

#include "Entity\Component.h"

class PlayerInput : public Component {
public:
	PlayerInput(json& args);
	~PlayerInput();
	void update() override;
	void init(json& j) override;

private:
	bool pausePressed_ = false;
};

