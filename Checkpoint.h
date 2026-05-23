#include "vec2.h"
#include <allegro5/allegro.h>
#include "Player.h"
#include <cmath>
#include "Collider.h"

class Checkpoint : public Collider {
private:
    const int _index;
public:

    Checkpoint(Utils::line* line, int index, float radius = 0.0f)
        : Collider(ColliderType::Checkpoint, line, radius, nullptr),
        _index(index)
    {}

	// --- Getter ---
    int Get_checkpoint_index() const { return _index; }
};