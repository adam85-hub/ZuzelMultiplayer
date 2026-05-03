
#include <vector>
#include <array>
#include "Player.h"
#include "math.h"
#include "vec2.h"
#include <allegro5/allegro_primitives.h>

struct Wall {
    Utils::vec2 a;
    Utils::vec2 b;
};

class WallDetector {
private:
	std::array<float, 7> offsets;
    std::vector<Player*> players;
	std::vector<Wall*> walls;

public:
    WallDetector();
    ~WallDetector();

	void AddPlayer(Player* player);
	void AddWall(Wall* wall);
	float CalculateDistance(const Player* player, const Wall* wall, float angle);
	void Update();
	void DrawSensors();
};