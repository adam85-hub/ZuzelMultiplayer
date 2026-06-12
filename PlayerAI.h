#pragma once
#include <allegro5/allegro_primitives.h>

#include "Player.h"
#include <memory>
#include "SpeedwayState.hpp"
#include <vector>
#include <array>
#include <cmath>
#include "line.h"

class PlayerAI : public Player {
public:
	PlayerAI(Utils::vec2 initial_position, ALLEGRO_BITMAP* bike_bitmap) : Player(initial_position, bike_bitmap) {}
	~PlayerAI() override = default;
	void Update(bool is_turning) override;
	void Render() const override;

	static void Set_walls(Utils::line* barriers_ptr, int count);
	static void Set_checkpoints(Utils::line* checkpoints_ptr, int count);

	std::shared_ptr<SpeedwayState> Get_player_state() const;
	
	//--- parametry do uczenia ---
	std::array<float, 8> _distances;
	//veclocity x,y policzy sie z velocity i angle
	//sin i cos policzy sie z angle
	float _checkpoint_distance;
	float _checkpoint_angle;//zostanie policzone sin i cos
	float _player_distance;
	float _player_angle;//zostanie policzone sin i cos
	//bool touching_wall = false; jest w class Player
	bool _is_hitting_player = false;
	bool _is_hitting_checkpoint = false;
	std::shared_ptr<SpeedwayState> _player_state;

private:
	Utils::vec2 _previous_position{ 0,0 };
	static Utils::line* _barriers; //bariers table
	static int _barriers_count;

	static Utils::line* _checkpoints; //checkpoints table
	static int _checkpoints_count;
	
	static const std::array<float, 8> _offsets;

	std::array<double, 2> calculate_velocity_components() const;
	
	//--- wall detector ---
	void draw_sensors() const;

	void update_sensors();
	float calculate_distance(const Utils::line* line, float angle);
	
	// --- checkpoint detector ---
	void update_distance_to_next_checkpoint();
	void update_degree_to_next_checkpoint();

	//--- debug ---
	void show_stats() const;

};
