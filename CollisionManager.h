#include "Collider.h"
#include "Checkpoint.h"
#include "PlayerAI.h"

#include <vector>

class CollisionManager {
private:
    std::vector<Collider*> _player_colliders;
    
    Utils::line* _barriers; //bariers table
	int _barriers_count;

	Utils::line* _checkpoints; //checkpoints table
    int _checkpoints_count;



    // --- Move ---
    void handle_collision_players(Collider* a, Collider* b);
    void handle_collision_barriers(Collider* a, Utils::line* barrier);

	// --- Check collision ---
    void manage_collision_barriers(Collider* a);
    void manage_collision_checkpoints(Collider* a);
	void manage_collision_player(Collider* a);


	// --- Dates to players AI ---
	void update_closest_player(Collider* c);
    
    static Utils::vec2 calculate_normal(Utils::vec2 collisionVector, Utils::vec2 wallVec);

public:

    ~CollisionManager();

	// --- Add Colidier ---
	void Add_player(Player* player, bool is_AI);
    void Set_barriers(Utils::line* barriers_ptr, int count);
	void Set_checkpoints(Utils::line* checkpoints_ptr, int count);

    // --- Debug ---
    void Draw_colliders();


	// --- Main Collision Check Loop ---
    void Update();    
};