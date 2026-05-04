#pragma once
#include <allegro5/allegro5.h>

#include "vec2.h"
#include <array>
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
	float acceleration(float v);
	float wall_deceleration(float v);

	ALLEGRO_BITMAP* _bike_bitmap;
	Utils::vec2 _bike_bitmap_size;

	const float _max_acceleration = 0.3;
	const float _optimal_engine_velocity = 7;
	const float _rotation_velocity = 1.f / c_FPS * .6f * M_PI;
	const float _max_velocity_offset = M_PI / 3;

	float _linear_velocity;
	float _rotation;
	float _velocity_offset;

	static int max_checkpoint;
	ALLEGRO_COLOR color;

	int _current_checkpoint_index = 0;
	int _laps_completed = 0;

public:
	std::array<float, 7> sensorDistances;
	const float& bike_height = _bike_bitmap_size.y;
	const float& bike_width = _bike_bitmap_size.x;
	bool touching_wall = false;

	Utils::vec2 position;

	//--- Getter ---
	float GetRotation() const { return _rotation; }
	int GetCurrentCheckpointIndex() const { return _current_checkpoint_index; }
	int GetLaps() const { return _laps_completed; }
	ALLEGRO_COLOR GetColor() const { return color; };

	//--- Setter ---
	void Move(Utils::vec2 force);
	void SetColor(ALLEGRO_COLOR new_color);

	//--- Checkpoint and Lap Management ---
	void updateCheckpointAndLap(int checkpointIndex);
};