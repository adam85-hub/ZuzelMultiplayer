#include <vector>
#include "Collider.h"


struct ClosestPoints {
    Utils::vec2 a;
    Utils::vec2 b;
};


class CollisionManager {
private:
    std::vector<Collider*> _colliders;


    // --- Move ---
    void HandleCollision(Collider* a, Collider* b);
    static ClosestPoints CalculateClosestPoints(Utils::vec2 p1, Utils::vec2 p2, Utils::vec2 p3, Utils::vec2 p4);

    static Utils::vec2 CalculateNormal(Utils::vec2 collisionVector, float distance, Utils::vec2 wallVec);

public:

    ~CollisionManager();

	// --- Add/Remove Colidier ---
    void AddCollider(Collider* c);
    void RemoveCollider(Collider* c);

    // --- Debug ---
    void DrawColliders();


	// --- Main Collision Check Loop ---
    void Update();

    
};