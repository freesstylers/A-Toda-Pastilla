#pragma once
#ifndef MENUMUESTRAPERSONAJE_H
#define MENUMUESTRAPERSONAJE_H

#include "Components/EntitySpawner.h"

class MenuMuestraPersonaje : public EntitySpawner
{
public:
	MenuMuestraPersonaje(json& args);
	~MenuMuestraPersonaje();
	void update() override;
	void init(json& j) override;

	void nextCharacter();
	void prevCharacter();
private:
	std::vector<std::string> entidades_;
	int n_ = 0;
	Vector3 pos_ = Vector3(0,0,0);
};

#endif // !MENUMUESTRAPERSONAJE_H
