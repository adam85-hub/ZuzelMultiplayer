#pragma once
#include <allegro5/allegro_primitives.h>

#include "Player.h"
#include <vector>
#include <array>
#include "line.h"

class PlayerAI : public Player {
public:
	PlayerAI(Utils::vec2 initial_position, ALLEGRO_BITMAP* bike_bitmap) : Player(initial_position, bike_bitmap) {}
	~PlayerAI() override = default;
	void Update(bool is_turning) override;
	void Render() const override;

	static void Add_walls(Utils::line* barriers_ptr, int count);
	static void Add_checkpoints(Utils::line* checkpoints_ptr, int count);
	
	Utils::line _player_line; // player "hitbox"

	//--- parametry do uczenia ---
	std::array<float, 8> _distances;
	//veclocity x,y policzy sie z velocity i angle
	//sin i cos policzy sie z angle
	float _checkpoint_distance;
	float _checkpoint_angle;//zostanie policzone sin i cos
	float _player_distance;
	float _player_angle;//zostanie policzone sin i cos
	//bool touching_wall = false; jest w class Player
	bool is_hitting_player = false;
	bool is_hitting_checkpoint = false;

private:
	static std::vector<Utils::line*> _walls;
	static std::vector<Utils::line*> _checkpoints;
	
	static const std::array<float, 8> _offsets;

	float calculate_distance(const Utils::line* line, float angle);
	
	//--- wall detector ---
	void update_sensors();
	void draw_sensors() const;
	
	// --- checkpoint detector ---
	void update_distance_to_next_checkpoint();
	void update_degree_to_next_checkpoint();


	//--- debug ---
	void show_stats() const;

	// --- set player line ---
	void update_player_line();
};
