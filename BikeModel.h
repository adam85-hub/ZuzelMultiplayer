#pragma once

#include "vec2.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Consts.h"

class BikeModel {
public:
	BikeModel();

	// Funkcja do uruchomienia raz w ka¿dej klatce. Zwraca wektor prêdkoœci
	Utils::vec2 Update(bool is_turning);

	float Get_rotation();
private:
	float acceleration_staights(float v);

	const float _max_acceleration = 0.7;
	const float _optimal_engine_velocity = 3;

	const float _rotation_velocity = 1.f/c_FPS * .5f * M_PI;

	float _velocity;
	float _rotation;
	bool _is_sliding;
}; 