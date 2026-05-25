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
	virtual ~Player();
	virtual void Update(bool is_turning);
	virtual void Render() const;

	void Move(Utils::vec2 v);
	void Update_checkpoint_and_lap(int checkpointIndex);
	void Finish(double time);

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

	int _current_checkpoint_index = 0;
	int _laps_completed = 0;
	bool _finished_race = false;
	double _race_time = -1;

public:
	static int checkpoint_count;
	const float& bike_height = _bike_bitmap_size.y;
	const float& bike_width = _bike_bitmap_size.x;
	const double& race_time = _race_time;
	bool touching_wall = false;

	Utils::vec2 position;

	//--- Getter ---
	float Get_rotation() const { return _rotation; }
	int Get_current_checkpoint_index() const { return _current_checkpoint_index; }
	int Get_laps() const { return _laps_completed; }
	int Get_laps_to_display() const;
	bool Has_finished() const { return _finished_race; }
};