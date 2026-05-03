#include "CollisionManager.h"

CollisionManager::~CollisionManager()
{
    for(auto* c : _colliders) {
        delete c;
	}
}

// --- Add/Remove Colidier ---
void CollisionManager::AddCollider(Collider* c)
{
	_colliders.push_back(c);
}

void CollisionManager::RemoveCollider(Collider* c)
{
    auto it = std::find(_colliders.begin(), _colliders.end(), c);
    if (it != _colliders.end()) {
        _colliders.erase(it);
	}
}



// --- Debug ---
void CollisionManager::DrawColliders()
{
    for (auto* c : _colliders)
    {
        if (c != nullptr)
        {
            ALLEGRO_COLOR color = c->GetColliding() ? al_map_rgb(255, 0, 0) : al_map_rgb(0, 255, 0);
            c->DrawDebug(color);
        }
    }
}





// --- Move ---
void CollisionManager::HandleCollision(Collider* a, Collider* b)
{
    
    ClosestPoints points = CalculateClosestPoints(
        a->GetStartPoint(), a->GetEndPoint(),
        b->GetStartPoint(), b->GetEndPoint()
    );


    Utils::vec2 colVec = points.a - points.b;
    float distance = std::sqrt(colVec.x * colVec.x + colVec.y * colVec.y);

    //is colision
    float combinedRadius = a->GetRadius() + b->GetRadius();
    float overlap = (combinedRadius - distance) + 0.05f;

    if (overlap <= 0) return;

    // 4. Oblicz normaln¹ i si³ê wypchniêcia
    Utils::vec2 wallVec = { b->GetEndPoint().x - b->GetStartPoint().x, b->GetEndPoint().y - b->GetStartPoint().y };
    Utils::vec2 normal = CalculateNormal(colVec, distance, wallVec);
    Utils::vec2 pushForce = { normal.x * overlap, normal.y * overlap };
    

    if (b->GetType() == ColliderType::Wall)
    {
        a->GetOwnerPlayer()->Move(pushForce);
		//obs³uga bandy przez adama
        a->GetOwnerPlayer()->touching_wall = true;
    }
	if (b->GetType() == ColliderType::Player)
    {
        a->GetOwnerPlayer()->Move({ pushForce.x * 0.5f, pushForce.y * 0.5f });
        b->GetOwnerPlayer()->Move({ pushForce.x * -0.5f, pushForce.y * -0.5f });
    }

    if(b->GetType() == ColliderType::Checkpoint)
    {
        a->GetOwnerPlayer()->updateCheckpointAndLap(b->GetCheckpointIndex());
    }

}



// --- Main Collision Check Loop ---
void CollisionManager::Update()
{
    for (auto* c : _colliders) {
        if (c != nullptr) c->ResetCollision();
        if (c != nullptr) c->UpdateHitbox();
    }

	for (int n = 0; n < 5; ++n) { ///brute force  zmiana parametrów mo¿e poprawiæ stabilnoœæ kolizji
        for (size_t i = 0; i < _colliders.size(); ++i)
        {
            for (size_t j = i + 1; j < _colliders.size(); ++j)
            {
                if (_colliders[i]->GetType() == ColliderType::Player) {
                    if (_colliders[i]->CheckCollision(*_colliders[j]))
                    {
                        // is colliding
                        _colliders[i]->SetColliding(true);
                        _colliders[j]->SetColliding(true);

                        HandleCollision(_colliders[i], _colliders[j]);

						_colliders[i]->UpdateHitbox(); //test DZIA£A LEPIEJ Z TYM
                        _colliders[j]->UpdateHitbox(); //test DZIA£A LEPIEJ Z TYM
                    }
                }
            }
        }
    }

}




ClosestPoints CollisionManager::CalculateClosestPoints(Utils::vec2 p1, Utils::vec2 p2, Utils::vec2 p3, Utils::vec2 p4)
{
    Utils::vec2 u = { p2.x - p1.x, p2.y - p1.y };
    Utils::vec2 v = { p4.x - p3.x, p4.y - p3.y };
    Utils::vec2 w = { p1.x - p3.x, p1.y - p3.y };

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

    return { { p1.x + sc * u.x, p1.y + sc * u.y }, { p3.x + tc * v.x, p3.y + tc * v.y } };
}


Utils::vec2 CollisionManager::CalculateNormal(Utils::vec2 collisionVector, float distance, Utils::vec2 wallVec)
{
    if (distance < 0.0001f) {
        
        float nx = -wallVec.y;
        float ny = wallVec.x;
        float nLen = std::sqrt(nx * nx + ny * ny);
        return (nLen > 0.0001f) ? Utils::vec2{ nx / nLen, ny / nLen } : Utils::vec2{ 0, 0 };
    }
    return { collisionVector.x / distance, collisionVector.y / distance };
}
