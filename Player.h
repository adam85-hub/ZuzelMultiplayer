#pragma once
#include <allegro5/allegro5.h>

#include "GameObject.h"
#include "vec2.h"

class Player : public GameObject {
public:
	// z bike_bitmap jest tworzona jej przeskalowana kopia. Po zakoñczeniu wykonywania siê konstruktora bitmapa pod adresem bike_bitmap nie jest ju¿ potrzebna
	Player(Utils::vec2 initial_position, ALLEGRO_BITMAP* bike_bitmap);
	~Player();
	void Update();
	void Render();

private:
	ALLEGRO_BITMAP* _bike_bitmap;
	Utils::vec2 _bike_bitmap_size;
public:
	const float& bike_height = _bike_bitmap_size.y;
	const float& bike_width = _bike_bitmap_size.x;
};