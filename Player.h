#pragma once
#include <allegro5/allegro5.h>

#include "GameObject.h"
#include "vec2.h"
#include "BikeModel.h"

class Player : public GameObject {
public:
	Player(Utils::vec2 initial_position, ALLEGRO_BITMAP* bike_bitmap);
	~Player();
	void Update(bool is_turning);
	void Render();

private:
	ALLEGRO_BITMAP* _bike_bitmap;
	Utils::vec2 _bike_bitmap_size;

	BikeModel _bike_model;
public:
	const float& bike_height = _bike_bitmap_size.y;
	const float& bike_width = _bike_bitmap_size.x;
};