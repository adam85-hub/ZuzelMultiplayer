#include "Collider.h"
#include <allegro5/allegro_primitives.h>

float Collider::GetDistanceBetweenSegments(Utils::vec2 p1, Utils::vec2 p2, Utils::vec2 p3, Utils::vec2 p4)
{
    Utils::vec2 u = p2 - p1;
    Utils::vec2 v = p4 - p3;
    Utils::vec2 w = p1 - p3;

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

///  stala
void Collider::UpdateHitbox()
{
	if (_owner == nullptr || _type == ColliderType::Wall) return;

	Utils::vec2 center = _owner->position;
	float angle = _owner->GetRotation();

	float halfLength = _owner->bike_height / 2.0f;

	float dirX = cos(-angle);
	float dirY = sin(-angle);

	_start_point.x = center.x - (dirX * halfLength)*1.7f;
	_start_point.y = center.y - (dirY * halfLength)*1.7f;

	_end_point.x = center.x + (dirX * halfLength)*1.7f;
	_end_point.y = center.y + (dirY * halfLength)*1.7f;
}


// --- COLLISION CHECKING ---
bool Collider::CheckCollision(const Collider& other) const
{
	float combinedRadius = this->_radius + other._radius;

	float dist = GetDistanceBetweenSegments(
		this->_start_point, this->_end_point,
		other._start_point, other._end_point
	);
	
	return dist <= combinedRadius;
}

// --- DEBUG ---
void Collider::DrawDebug(ALLEGRO_COLOR color)
{
	float thickness = _radius * 2.0f;
	if (thickness < 1.0f) thickness = 1.0f;

	al_draw_line(
		_start_point.x, _start_point.y,
		_end_point.x, _end_point.y,
		color,thickness);

	if (_radius > 1.0f) {
		al_draw_filled_circle(_start_point.x, _start_point.y, _radius, color);
		al_draw_filled_circle(_end_point.x, _end_point.y, _radius, color);
	}

}
