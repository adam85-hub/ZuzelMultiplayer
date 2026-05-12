#pragma once
#include <allegro5/allegro.h>
#include <cmath>

#include "Player.h"
#include "vec2.h"
#include "line.h"

enum class ColliderType {
    Player,
    Wall,
	Checkpoint
};

class Collider {
private:
    const ColliderType _type;
    Utils::line* const _line;
    const float _radius;

    Player* const _owner;
	


public:
    Collider(ColliderType type, Utils::line* line, float radius = 0.0f, Player* owner = nullptr) : 
            _type(type),_line(line), _owner(owner), _radius(radius){};
    ~Collider();
    
    // debug
    bool is_colliding = false;

    //algorytm Dan Sunday
    static float Get_distance_between_lines(const Utils::line& l1, const Utils::line& l2);

    // --- GETTERY ---
    Player* Get_owner_player() const { return _owner; }
	const Utils::line* Get_line() const { return _line; }

    float Get_radius() const { return _radius; }
    ColliderType Get_type() const { return _type; }

	// --- Collision Detection ---
    void Update_hitbox();
	bool Check_collision(const Collider& other) const;

	// --- Debug ---
    void Draw_debug(ALLEGRO_COLOR color);
};