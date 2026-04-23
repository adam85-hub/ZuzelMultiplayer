#include "Player.h"
#include <algorithm>

// z bike_bitmap jest tworzona jej przeskalowana kopia. Po zakoñczeniu wykonywania siê konstruktora bitmapa pod adresem bike_bitmap nie jest ju¿ potrzebna
Player::Player(Utils::vec2 initial_position, ALLEGRO_BITMAP* bike_bitmap) : 
	position(initial_position),
	_linear_velocity(0),
	_rotation(0),
	_velocity_offset(0)
{
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
	_linear_velocity += acceleration(_linear_velocity);

	if (is_turning) {
		_rotation = _rotation + _rotation_velocity;
		_velocity_offset = std::min(_velocity_offset + (float)(M_PI / 3) / c_FPS, (float)M_PI / 3); //drifty

		if (_rotation > 2 * M_PI)
			_rotation -= 2 * M_PI; // żeby wartość kąta nie zrobiła się zbyt duża
	}
	else
		_velocity_offset = std::max(_velocity_offset * 0.955f, 0.f); // zmniejszanie driftu

	Utils::vec2 velocity;
	velocity.x = _linear_velocity * cosf(_rotation - _velocity_offset);
	velocity.y = -1 * _linear_velocity * sinf(_rotation - _velocity_offset);
	velocity = velocity;

	position = position + velocity;
}

void Player::Render() {
	al_draw_rotated_bitmap(_bike_bitmap, _bike_bitmap_size.x / 2, _bike_bitmap_size.y / 2, position.x, position.y, -_rotation, 0);
}

float Player::acceleration(float velocity) {
	if (velocity == 0)
		return _max_acceleration;

	//float a = _max_acceleration * (1 - powf((velocity - _optimal_engine_velocity) / _optimal_engine_velocity, 2));
	float a = _max_acceleration * powf(velocity / _optimal_engine_velocity - 1, 2);

	return std::max(.0f, a); // zabezpieczenie aby przyspieszenie nie było ujemne
}

void Player::Move(Utils::vec2 force)
{
	position = position + force;
}
