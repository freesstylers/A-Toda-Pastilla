#pragma once
#include "Entity/Component.h"

class EutanasiaTexto : public Component
{
public:
	EutanasiaTexto(json& args);
	~EutanasiaTexto();
	void init(json& j) override;
	void start() override;
	void update() override;
	bool ReceiveEvent(Event& event) override;
private:
	bool bombazo = false;
	float cooldown = 0.0f;
};

