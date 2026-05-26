#pragma once
#include <allegro5/allegro.h>
#include <cmath>

#include "Player.h"
#include "vec2.h"
#include "line.h"

class Collider {
private:
    Player* const _owner;
    const float _radius;
	const bool _is_AI;

public:
    Collider(Player* owner, bool is_AI) :
            _owner(owner), _radius(c_THICKNESS_HITBOX_PLAYER), _is_AI(is_AI) {};
    
    // debug
    bool is_colliding = false;

    // --- GETTERY ---
    Player* Get_owner_player() const { return _owner; }
    float Get_radius() const { return _radius; }
	bool Is_AI() const { return _is_AI; }

    void Update_hitbox();
    bool Check_collision(const Collider& other) const;
	
	// --- Debug ---
    void Draw_debug(ALLEGRO_COLOR color);
};
