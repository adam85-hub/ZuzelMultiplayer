#include "PlayerAI.h"

std::vector<Utils::line*> PlayerAI::_walls;
const std::array<float, 7> PlayerAI::_offsets = { -0.5f, -0.3f, -0.1f, 0.0f, 0.1f, 0.3f, 0.5f };

void PlayerAI::Add_walls(Utils::line* barriers_ptr, int count)
{
	for (int i = 0; i < count; ++i)
	{
		_walls.push_back(&barriers_ptr[i]);
	}
}

float PlayerAI::calculate_distance(const Utils::line* wall, float angle)
{
    Utils::vec2 dir = { cosf(-angle), sinf(-angle) };

    Utils::vec2 start = wall->a;
    Utils::vec2 end = wall->b;
    Utils::vec2 wallVec = { end.x - start.x, end.y - start.y };

    float det = dir.x * wallVec.y - dir.y * wallVec.x;

    if (std::abs(det) < 1e-6f) return -1.0f;

    Utils::vec2 diff = { start.x - this->position.x, start.y - this->position.y };

    float t = (diff.x * wallVec.y - diff.y * wallVec.x) / det;
    float u = (diff.x * dir.y - diff.y * dir.x) / det;

    if (t > 0 && u >= 0.0f && u <= 1.0f) {
        return t; 
    }

    return -1.0f; 
}

// --- Update ---
void PlayerAI::update_sensors() {
    float playerRot = this->Get_rotation();

    for (size_t i = 0; i < _offsets.size(); ++i) {
        float rayAngle = playerRot + _offsets[i];

        float minDistance = std::numeric_limits<float>::max();
        bool hit = false;

        for (const auto& wall : _walls) {

            float dist = calculate_distance(wall, rayAngle);

            // Szukamy najbli¿szej œciany
            if (dist > 0 && dist < minDistance) {
                minDistance = dist;
                hit = true;
            }
        }

        _sensor_distances[i] = hit ? minDistance : -1.0f;
    }
}

void PlayerAI::Update(bool is_turning) {

    Player::Update(is_turning);

    this->update_sensors();
   
};

// --- Render ---
void PlayerAI::draw_sensors() const {
    ALLEGRO_COLOR laserColor = al_map_rgb(255, 0, 0);

    float playerRot = this->Get_rotation();

    for (size_t i = 0; i < _offsets.size(); ++i) {
        float angle = playerRot + _offsets[i];

        float dist = _sensor_distances[i];

        float lineLength = (dist > 0) ? dist : 150.0f;

        float endX = this->position.x + cosf(-angle) * lineLength;
        float endY = this->position.y + sinf(-angle) * lineLength;

        al_draw_line(this->position.x, this->position.y, endX, endY, laserColor, 1.0f);
    }
}

void PlayerAI::Render() const {
    Player::Render();
    this->draw_sensors();
}








