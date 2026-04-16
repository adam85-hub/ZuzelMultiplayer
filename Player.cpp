#include "Player.h"

#define _USE_MATH_DEFINES
#include <math.h>

Player::Player(Utils::vec2 initial_position, ALLEGRO_BITMAP* bike_bitmap) : _position(initial_position) {
	constexpr float scale = 2;
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

void Player::Update() {

}

void Player::Render() {
	al_draw_rotated_bitmap(_bike_bitmap, _bike_bitmap_size.x / 2, _bike_bitmap_size.y / 2, _position.x, _position.y, 0, 0);
}