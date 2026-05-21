#include "vec2.h"
#include <allegro5/allegro.h>
#include "Player.h"
#include <cmath>
#include "Collider.h"

class Checkpoint : public Collider {
private:
    static int _next_id;
    const int _index;
public:

    Checkpoint(Utils::line* line, float radius = 0.0f)
        : Collider(ColliderType::Checkpoint, line, radius, nullptr),
        _index(_next_id++)
    {}

	// --- Getter ---
    int Get_checkpoint_index() const { return _index; }
};