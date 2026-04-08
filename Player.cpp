#include "Player.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "draw_polish_text.h"

// z bike_bitmap jest tworzona jej przeskalowana kopia. Po zakoñczeniu wykonywania siê konstruktora bitmapa pod adresem bike_bitmap nie jest ju¿ potrzebna
Player::Player(Utils::vec2 initial_position, ALLEGRO_BITMAP* bike_bitmap) : GameObject(initial_position) {
	constexpr float scale = 1.7;
	_bike_bitmap_size.x = al_get_bitmap_width(bike_bitmap) * scale;
	_bike_bitmap_size.y = al_get_bitmap_height(bike_bitmap) * scale;

	_bike_bitmap = al_create_bitmap(_bike_bitmap_size.x, _bike_bitmap_size.y);
	al_set_target_bitmap(_bike_bitmap);
	al_draw_scaled_bitmap(bike_bitmap, 0, 0, al_get_bitmap_width(bike_bitmap), al_get_bitmap_height(bike_bitmap),
		0, 0, _bike_bitmap_size.x, _bike_bitmap_size.y, 0);
	al_convert_mask_to_alpha(_bike_bitmap, al_map_rgb(0, 0, 0));
	al_set_target_backbuffer(al_get_current_display());
};

Player::~Player() {
	al_destroy_bitmap(_bike_bitmap);
}

void Player::Update(bool is_turning) {
	Utils::vec2 velocity = _bike_model.Update(is_turning);

	position = position + velocity;
}

void Player::Render() {
	al_draw_rotated_bitmap(_bike_bitmap, _bike_bitmap_size.x / 2, _bike_bitmap_size.y / 2, position.x, position.y,
		-_bike_model.Get_rotation(), 0);
}