#pragma once

#include "Events/Event.h"

//Los nuevos eventos que se creen, heredan de Event y luego se hace un casteo
//para acceder a los datos --> static_cast<EventPuntuacion&>(event).puntuacion_

struct EventPuntuacion : public Event {
public:
	inline EventPuntuacion(int puntuacion) : Event("EnemyDeath") {
		this->puntuacion_ = puntuacion;
	};

	int puntuacion_ = 0;
};