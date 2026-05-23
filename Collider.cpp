#include "Collider.h"

#include <allegro5/allegro_primitives.h>
#include <stdexcept>

Collider::~Collider()
{
    if(_type == ColliderType::Player) {
        delete _line;
    }
}

float Collider::Get_distance_between_lines(const Utils::line& l1, const Utils::line& l2)
{
    Utils::vec2 u = l1.b - l1.a;
    Utils::vec2 v = l2.b - l2.a;
    Utils::vec2 w = l1.a - l2.a;

    float a = u.dot(u);
    float b = u.dot(v);
    float c = v.dot(v);
    float d = u.dot(w);
    float e = v.dot(w);
    float D = a * c - b * b;
    float sc, sN, sD = D;
    float tc, tN, tD = D;

    if (D < 1e-4f) {
        sN = 0.0f; sD = 1.0f;
        tN = e; tD = c;
    }
    else {
        sN = (b * e - c * d);
        tN = (a * e - b * d);
        if (sN < 0.0f) { sN = 0.0f; tN = e; tD = c; }
        else if (sN > sD) { sN = sD; tN = e + b; tD = c; }
    }

    if (tN < 0.0f) {
        tN = 0.0f;
        if (-d < 0.0f) sN = 0.0f;
        else if (-d > a) sN = sD;
        else { sN = -d; sD = a; }
    }
    else if (tN > tD) {
        tN = tD;
        if ((-d + b) < 0.0f) sN = 0;
        else if ((-d + b) > a) sN = sD;
        else { sN = (-d + b); sD = a; }
    }

    sc = (std::abs(sN) < 1e-4f ? 0.0f : sN / sD);
    tc = (std::abs(tN) < 1e-4f ? 0.0f : tN / tD);

    Utils::vec2 dP = w + (u * sc) - (v * tc);
    return std::sqrt(dP.dot(dP));
}


void Collider::Update_hitbox()
{
    if (_type != ColliderType::Player) {
        throw std::runtime_error("Update_hitbox called on non-player collider");
    }

    if (_owner == nullptr) {
        throw std::logic_error("Update_hitbox called on collider with null owner");
    }

    //if (_owner == nullptr || _type == ColliderType::Wall)return;


	Utils::vec2 center = _owner->position;
	float angle = _owner->Get_rotation();

	float halfLength = _owner->bike_height / 2.0f;

	float dirX = cos(-angle);
	float dirY = sin(-angle);

    _line->a.x = center.x - (dirX * halfLength)*1.7f;
    _line->a.y = center.y - (dirY * halfLength)*1.7f;

    _line->b.x = center.x + (dirX * halfLength)*1.7f;
    _line->b.y = center.y + (dirY * halfLength)*1.7f;
}


// --- COLLISION CHECKING ---
bool Collider::Check_collision(const Collider& other) const
{
	float combinedRadius = this->_radius + other._radius;

    float dist = Get_distance_between_lines(*this->_line, *other._line);
	
	return dist <= combinedRadius;
}

// --- DEBUG ---
void Collider::Draw_debug(ALLEGRO_COLOR color)
{
	float thickness = _radius * 2.0f;
	if (thickness < 1.0f) thickness = 1.0f;

    al_draw_line(
        _line->a.x, _line->a.y,
        _line->b.x, _line->b.y,
        color, thickness);

    if (_radius > 1.0f) {
        al_draw_filled_circle(_line->a.x, _line->a.y, _radius, color);
        al_draw_filled_circle(_line->b.x, _line->b.y, _radius, color);
    }

}

