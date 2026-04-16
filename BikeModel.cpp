#include "BikeModel.h"

#include <algorithm>
#include "LOG.h"

BikeModel::BikeModel() : 
	_is_sliding(false),
	_velocity(0),
	_rotation(0)
{

}

Utils::vec2 BikeModel::Update(bool is_turning) {
	_velocity += acceleration_staights(_velocity);

	if (is_turning) {
		_rotation = _rotation + _rotation_velocity;

		if (_rotation > 2 * M_PI)
			_rotation -= 2 * M_PI; // ¿eby wartoœæ k¹ta nie zrobi³a siê zbyt du¿a
	}

	Utils::vec2 velocity;
	velocity.x = _velocity * cosf(_rotation);
	velocity.y = -1 * _velocity * sinf(_rotation);

	return velocity;
}

float BikeModel::Get_rotation() {
	return _rotation;
}

float BikeModel::acceleration_staights(float velocity) {
	if (velocity == 0)
		return _max_acceleration;

	//float a = _max_acceleration * (1 - powf((velocity - _optimal_engine_velocity) / _optimal_engine_velocity, 2));
	float a = _max_acceleration * powf(velocity/_optimal_engine_velocity - 1, 2);

	return std::max(.0f, a); // zabezpieczenie aby przyspieszenie nie by³o ujemne
}