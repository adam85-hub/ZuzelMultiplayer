#include "CollisionManager.h"
#include "Consts.h"

CollisionManager::~CollisionManager()
{
    for(auto* c : _player_colliders) {
        delete c;
	}
}

void CollisionManager::Add_player(Player* player, bool is_AI)
{
    _player_colliders.emplace_back(new Collider(player, is_AI));
}

void CollisionManager::Set_barriers(Utils::line* barriers_ptr, int count)
{
	_barriers = barriers_ptr;
	_barriers_count = count;
}

void CollisionManager::Set_checkpoints(Utils::line* checkpoints_ptr, int count)
{
	_checkpoints = checkpoints_ptr;
	_checkpoints_count = count;
}

// --- Debug ---
void CollisionManager::Draw_colliders()
{
    for (auto* c : _player_colliders)
    {
        if (c != nullptr)
        {
            ALLEGRO_COLOR color = c->is_colliding ? al_map_rgb(255, 0, 0) : al_map_rgb(0, 255, 0);
            c->Draw_debug(color);
        }
    }
}


// --- Move ---
void CollisionManager::handle_collision_players(Collider* a, Collider* b)
{   


    const Utils::line& lineA = a->Get_owner_player()->line_postion;
    const Utils::line& lineB = b->Get_owner_player()->line_postion;

    Utils::line points = lineA.get_closest_points(lineB);

    Utils::vec2 colVec = points.a - points.b;

    float combinedRadius = a->Get_radius() + b->Get_radius();
    float overlap = (combinedRadius - colVec.Length()) + 0.05f;

    const Utils::vec2 wallVec = lineB.b - lineB.a;
    const Utils::vec2 normal = calculate_normal(colVec, wallVec);
    const Utils::vec2 pushForce = { normal.x * overlap, normal.y * overlap };
        
    a->Get_owner_player()->Move({ pushForce.x * 0.5f, pushForce.y * 0.5f });
    b->Get_owner_player()->Move({ pushForce.x * -0.5f, pushForce.y * -0.5f });

}

void CollisionManager::handle_collision_barriers(Collider* a, Utils::line* barrier)
{
    const Utils::line& lineA = a->Get_owner_player()->line_postion;

    //Znalezienie punktów kolizji
    Utils::line points = lineA.get_closest_points(*barrier);

    //Wektor kolizji: od punktu na barierze do punktu na graczu
    Utils::vec2 colVec = points.a - points.b;

    //Obliczenie overlap
    float combinedRadius = a->Get_radius();
    float overlap = (combinedRadius - colVec.Length()) + 0.05f;

    //Obliczenie normalnej
    const Utils::vec2 wallVec = barrier->b - barrier->a;
    const Utils::vec2 normal = calculate_normal(colVec, wallVec);

    //Wypchnięcie gracza
    Utils::vec2 pushForce = { normal.x * overlap, normal.y * overlap };
    a->Get_owner_player()->Move(pushForce);

}

void CollisionManager::Update()
{
    for (auto* c : _player_colliders) {
        c->is_colliding = false;
        c->Get_owner_player()->touching_wall = false;
        if (c->Is_AI()) {//dane do AI
            PlayerAI* ai = static_cast<PlayerAI*>(c->Get_owner_player());
			ai->_is_hitting_checkpoint = false;
            ai->_is_hitting_player = false;
        }
    }

    for (int n = 0; n < 5; ++n) {
        for (auto* c : _player_colliders) {

            c->Update_hitbox();

            Utils::line player_line = c->Get_owner_player()->line_postion;
            float radius = c->Get_radius();

            // --- BARRIERS ---
            for (int i = 0; i < _barriers_count; i++) {

                bool is_overlapping = player_line.get_distance(_barriers[i]) <= (radius + 0.05f);

                if (is_overlapping) {
                    c->is_colliding = true; //debug

                    c->Get_owner_player()->touching_wall = true;
                    handle_collision_barriers(c, &_barriers[i]);
                }
            }

            // --- CHECKPOINTS ---
            int current_checkpoint_index = c->Get_owner_player()->Get_current_check_point_index();

            if (player_line.get_distance(_checkpoints[current_checkpoint_index]) <= (radius + 1.5f)) {
				c->Get_owner_player()->Update_checkpoint_and_lap(current_checkpoint_index);

                if (c->Is_AI()) {//dane do AI
                    PlayerAI* ai = static_cast<PlayerAI*>(c->Get_owner_player());
					ai->_is_hitting_checkpoint = true;
                }
            }

            // --- PLAYERS ---
            for (auto* others : _player_colliders) {
                if (c == others) continue; // z samym sobą nie koliduje
                if (c->Check_collision(*others)) {
                    c->is_colliding = true;
                    others->is_colliding = true;

                    if (c->Is_AI()) {//dane do AI
                        PlayerAI* ai = static_cast<PlayerAI*>(c->Get_owner_player());
                        ai->_is_hitting_player = true;
                    }

                    handle_collision_players(c, others);
                }
            }

        }
    }

}

Utils::vec2 CollisionManager::calculate_normal(Utils::vec2 collisionVector, Utils::vec2 wallVec)
{
    if (collisionVector.Length() < 0.0001f)
    {
        return wallVec.GetPerpendicular().GetNormalized();
    }

    return collisionVector.GetNormalized();
}
