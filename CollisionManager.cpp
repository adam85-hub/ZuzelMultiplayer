#include "CollisionManager.h"
#include "Consts.h"

CollisionManager::~CollisionManager()
{
    for(auto* c : _colliders) {
        delete c;
	}
}

void CollisionManager::Add_player(Player* player)
{
    Utils::vec2 center = player->position;

    float halfLength = player->bike_height / 2.0f;
    float angle = player->Get_rotation();

    float dirX = cos(-angle);
    float dirY = sin(-angle);

	Utils::vec2 a,b;
    a.x = center.x - (dirX * halfLength) * 1.7f;
    a.y = center.y - (dirY * halfLength) * 1.7f;

    b.x = center.x + (dirX * halfLength) * 1.7f;
    b.y = center.y + (dirY * halfLength) * 1.7f;


    Utils::line* line = new Utils::line{ a, b };
	_colliders.emplace_back(new Collider(ColliderType::Player, line, c_THICKNESS_HITBOX_PLAYER, player));
}

void CollisionManager::Add_walls(Utils::line* barriers_ptr, int count)
{
    for (int i = 0; i < count; ++i)
    {
        _colliders.emplace_back(new Collider(ColliderType::Wall, &barriers_ptr[i] ,c_THICKNESS_HITBOX_WALL));
	}
}

void CollisionManager::Add_checkpoints(Utils::line* checkpoint_ptr, int count)
{
    for (int i = 0; i < count; ++i)
    {
        _colliders.emplace_back(new Checkpoint(&checkpoint_ptr[i], c_THICKNESS_HITBOX_CHECKPOINT));
    }
}


// --- Debug ---
void CollisionManager::Draw_colliders()
{
    for (auto* c : _colliders)
    {
        if (c != nullptr)
        {
            ALLEGRO_COLOR color = c->is_colliding ? al_map_rgb(255, 0, 0) : al_map_rgb(0, 255, 0);
            c->Draw_debug(color);
        }
    }
}


// --- Move ---
void CollisionManager::handle_collision(Collider* a, Collider* b)
{
    const Utils::line& lineA = *a->Get_line();
    const Utils::line& lineB = *b->Get_line();

    ClosestPoints points = calculate_closest_points(lineA, lineB);

    Utils::vec2 colVec = points.a - points.b;

    //is colision
    float combinedRadius = a->Get_radius() + b->Get_radius();
    float overlap = (combinedRadius - colVec.Length()) + 0.05f;

    const Utils::vec2 wallVec = lineB.b - lineB.a;
    const Utils::vec2 normal = calculate_normal(colVec, wallVec);
    const Utils::vec2 pushForce = { normal.x * overlap, normal.y * overlap };
    

    if (b->Get_type() == ColliderType::Wall)
    {
        a->Get_owner_player()->Move(pushForce);
        a->Get_owner_player()->touching_wall = true;
    }

	if (b->Get_type() == ColliderType::Player)
    {
        a->Get_owner_player()->Move({ pushForce.x * 0.5f, pushForce.y * 0.5f });
        b->Get_owner_player()->Move({ pushForce.x * -0.5f, pushForce.y * -0.5f });
    }

    if(b->Get_type() == ColliderType::Checkpoint)
    {
        Checkpoint* cp = static_cast<Checkpoint*>(b);

        int index = cp->Get_checkpoint_index();

        a->Get_owner_player()->Update_checkpoint_and_lap(index);
    }

}



// --- Main Collision Check Loop ---
void CollisionManager::Update()
{
    for (auto* c : _colliders) {
        if (c != nullptr){
            c->is_colliding = false;//debug info

            if(c->Get_type() == ColliderType::Player) c->Update_hitbox();
        } 
    }

	for (int n = 0; n < 5; ++n) { ///brute force  zmiana parametrÃ³w moÂ¿e poprawiÃ¦ stabilnoÅ“Ã¦ kolizji
        for (size_t i = 0; i < _colliders.size(); ++i)
        {   
            if (_colliders[i]->Get_type() != ColliderType::Player) continue;

            for (size_t j = i + 1; j < _colliders.size(); ++j)
            {
                if (!_colliders[i]->Check_collision(*_colliders[j]))continue;

                    // is colliding
                    _colliders[i]->is_colliding = true;
                    _colliders[j]->is_colliding = true;

                    handle_collision(_colliders[i], _colliders[j]);

				    _colliders[i]->Update_hitbox();
                    if(_colliders[j]->Get_type()==ColliderType::Player) _colliders[j]->Update_hitbox();    
            }
        }
    }

}



ClosestPoints CollisionManager::calculate_closest_points(const Utils::line& l1, const Utils::line& l2)
{
    Utils::vec2 u = l1.b - l1.a;
    Utils::vec2 v = l2.b - l2.a;
    Utils::vec2 w = l1.a - l2.a;

    float a_dot = u.dot(u);
    float b_dot = u.dot(v);
    float c_dot = v.dot(v);
    float d_dot = u.dot(w);
    float e_dot = v.dot(w);

    float D = a_dot * c_dot - b_dot * b_dot;
    float sc, sN, sD = D;
    float tc, tN, tD = D;

    if (D < 0.0001f) {
        sN = 0.0f; sD = 1.0f; tN = e_dot; tD = c_dot;
    }
    else {
        sN = (b_dot * e_dot - c_dot * d_dot);
        tN = (a_dot * e_dot - b_dot * d_dot);
        if (sN < 0.0f) { sN = 0.0f; tN = e_dot; tD = c_dot; }
        else if (sN > sD) { sN = sD; tN = e_dot + b_dot; tD = c_dot; }
    }

    if (tN < 0.0f) {
        tN = 0.0f;
        if (-d_dot < 0.0f) sN = 0.0f;
        else if (-d_dot > a_dot) sN = sD;
        else { sN = -d_dot; sD = a_dot; }
    }
    else if (tN > tD) {
        tN = tD;
        if ((-d_dot + b_dot) < 0.0f) sN = 0;
        else if ((-d_dot + b_dot) > a_dot) sN = sD;
        else { sN = (-d_dot + b_dot); sD = a_dot; }
    }

    sc = (std::abs(sN) < 0.0001f ? 0.0f : sN / sD);
    tc = (std::abs(tN) < 0.0001f ? 0.0f : tN / tD);

    return {
        l1.a + (u * sc),
        l2.a + (v * tc)
    };
}


Utils::vec2 CollisionManager::calculate_normal(Utils::vec2 collisionVector, Utils::vec2 wallVec)
{
    float distance = collisionVector.Length();
    if (distance < 0.0001f) {
        
        float nx = -wallVec.y;
        float ny = wallVec.x;
        float nLen = std::sqrt(nx * nx + ny * ny);
        return (nLen > 0.0001f) ? Utils::vec2{ nx / nLen, ny / nLen } : Utils::vec2{ 0, 0 };
    }
    return { collisionVector.x / distance, collisionVector.y / distance };
}
