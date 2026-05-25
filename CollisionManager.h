#include "Collider.h"
#include "Checkpoint.h"

#include <vector>

class CollisionManager {
private:
    std::vector<Collider*> _colliders;


    // --- Move ---
    void handle_collision(Collider* a, Collider* b);
    static Utils::line calculate_closest_points(const Utils::line& l1, const Utils::line& l2);

    static Utils::vec2 calculate_normal(Utils::vec2 collisionVector, Utils::vec2 wallVec);

public:

    ~CollisionManager();

	// --- Add Colidier ---
	void Add_player(Player* player);
    void Add_walls(Utils::line* barriers_ptr, int count);
	void Add_checkpoints(Utils::line* checkpoint_ptr, int count);

    // --- Debug ---
    void Draw_colliders();


	// --- Main Collision Check Loop ---
    void Update();    
};