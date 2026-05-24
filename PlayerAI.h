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
	
	//Tutaj Henryk pobiera dystans
	std::array<float, 7> _sensor_distances;
	float _distance_to_next_checkpoint;
	float _degree_to_next_checkpoint;

private:
	static std::vector<Utils::line*> _walls;
	//static std::vector<Utils::line*> _checkpoints;

	static const std::array<float, 7> _offsets;

	float calculate_distance(const Utils::line* line, float angle);
	
	//--- wall detector ---
	void update_sensors();
	void draw_sensors() const;
	
	// --- checkpoint detector ---
	//void update_distance_to_next_checkpoint();
	//void update_degree_to_next_checkpoint();
};
