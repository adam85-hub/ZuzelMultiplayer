#pragma once
#include <allegro5/allegro5.h>

#include "vec2.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Consts.h"


class Player {
public:
	Player(Utils::vec2 initial_position, ALLEGRO_BITMAP* bike_bitmap);
	~Player();
	void Update(bool is_turning);
	void Render();

private:
	float acceleration_staights(float v);

	ALLEGRO_BITMAP* _bike_bitmap;
	Utils::vec2 _bike_bitmap_size;

	const float _max_acceleration = 0.3;
	const float _optimal_engine_velocity = 3.5;
	const float _rotation_velocity = 1.f / c_FPS * .7f * M_PI;

	float _linear_velocity;
	float _rotation;
public:
	const float& bike_height = _bike_bitmap_size.y;
	const float& bike_width = _bike_bitmap_size.x;

	Utils::vec2 position;

	//--- Getter ---
	float GetRotation() const { return _rotation; }

	//--- Setter ---
	void Move(Utils::vec2 force);
};