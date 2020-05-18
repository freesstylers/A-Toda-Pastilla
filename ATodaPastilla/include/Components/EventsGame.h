#pragma once

#include "Events/Event.h"


struct EventPuntuacion : public Event {
public:
	inline EventPuntuacion(int puntuacion) : Event("EnemyDeath") {
		this->puntuacion_ = puntuacion;
	};

	int puntuacion_ = 0;
};