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
	void Render() override;

	static void Add_walls(Utils::line* barriers_ptr, int count);
	
	//Tutaj Henryk pobiera dystans
	std::array<float, 7> _sensor_distances;

private:
	static std::vector<Utils::line*> _walls;
	static const std::array<float, 7> _offsets;

	
	void update_sensors();
	void draw_sensors();
	
	float calculate_distance(const Utils::line* wall, float angle);
};
