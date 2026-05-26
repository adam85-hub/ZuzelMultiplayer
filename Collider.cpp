#include "Collider.h"

#include <allegro5/allegro_primitives.h>
#include <stdexcept>


void Collider::Update_hitbox()
{
    if (_owner == nullptr) {
        throw std::logic_error("Update_hitbox called on collider with null owner");
    }

	Utils::vec2 center = _owner->position;
	float angle = _owner->Get_rotation();

	float halfLength = _owner->bike_height / 2.0f;

	float dirX = cosf(-angle);
	float dirY = sinf(-angle);

    
    _owner->line_postion.a.x = center.x - (dirX * halfLength)*1.7f;
    _owner->line_postion.a.y = center.y - (dirY * halfLength)*1.7f;

    _owner->line_postion.b.x = center.x + (dirX * halfLength)*1.7f;
    _owner->line_postion.b.y = center.y + (dirY * halfLength)*1.7f;
}

// --- COLLISION CHECKING ---
bool Collider::Check_collision(const Collider& other) const
{
    float combinedRadius = this->_radius + other._radius;

	float dist = _owner->line_postion.get_distance(other._owner->line_postion);

    return dist <= combinedRadius;
}

// --- DEBUG ---
void Collider::Draw_debug(ALLEGRO_COLOR color)
{
	float thickness = _radius * 2.0f;
	if (thickness < 1.0f) thickness = 1.0f;

    Utils::line _line = _owner->line_postion;

    al_draw_line(
        _line.a.x, _line.a.y,
        _line.b.x, _line.b.y,
        color, thickness);

    if (_radius > 1.0f) {
        al_draw_filled_circle(_line.a.x, _line.a.y, _radius, color);
        al_draw_filled_circle(_line.b.x, _line.b.y, _radius, color);
    }

}

