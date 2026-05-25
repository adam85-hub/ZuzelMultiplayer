#pragma once
#include <allegro5/allegro5.h>

#include "vec2.h"
#include "line.h"
#include <array>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Consts.h"

class Player {
public:
	Player(Utils::vec2 initial_position, ALLEGRO_BITMAP* bike_bitmap);
	virtual ~Player();
	virtual void Update(bool is_turning);
	virtual void Render() const;

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

	ALLEGRO_COLOR _color;

	int _current_checkpoint_index = 0;
	int _laps_completed = 0;

public:
	static int checkpoint_count;
	const float& bike_height = _bike_bitmap_size.y;
	const float& bike_width = _bike_bitmap_size.x;
	bool touching_wall = false;

	Utils::vec2 position;
	Utils::line line_postion; //liczenie odlegoœci od motora

	//--- Getter ---
	float Get_rotation() const { return _rotation; }
	int Get_current_check_point_index() const { return _current_checkpoint_index; }
	int Get_laps() const { return _laps_completed; }
	ALLEGRO_COLOR Get_color() const { return _color; };

	//--- Setter ---
	void Move(Utils::vec2 v);
	void Set_color(ALLEGRO_COLOR new_color);

	//--- Checkpoint and Lap Management ---
	void Update_checkpoint_and_lap(int checkpointIndex);
};