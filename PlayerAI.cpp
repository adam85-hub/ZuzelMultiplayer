#include "PlayerAI.h"
#include <iostream>

std::vector<Utils::line*> PlayerAI::_walls;
std::vector<Utils::line*> PlayerAI::_checkpoints;

const std::array<float, 8> PlayerAI::_offsets = { -1.5f, -0.5f, -0.25f, 0.0f, 0.25f, 0.50f, 1.5f ,2.4f};

void PlayerAI::Add_walls(Utils::line* barriers_ptr, int count)
{
	for (int i = 0; i < count; ++i)
	{
		_walls.push_back(&barriers_ptr[i]);
	}
}

void PlayerAI::Add_checkpoints(Utils::line* checkpoints_ptr, int count)
{
    for (int i = 0; i < count; ++i)
    {
        _checkpoints.push_back(&checkpoints_ptr[i]);
    }
}


float PlayerAI::calculate_distance(const Utils::line* line, float angle)
{
    Utils::vec2 dir = { cosf(-angle), sinf(-angle) };

    Utils::vec2 start = line->a;
    Utils::vec2 end = line->b;
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

        _distances[i] = hit ? minDistance : -1.0f;
    }
}


void PlayerAI::Update(bool is_turning) {

    Player::Update(is_turning);

    this->update_sensors();
    this->update_player_line();
    this->update_distance_to_next_checkpoint();
	this->update_degree_to_next_checkpoint();
};

void PlayerAI::Render() const {
    Player::Render();
    this->draw_sensors();
    this->show_stats();
}

// --- Render ---
void PlayerAI::draw_sensors() const {
    ALLEGRO_COLOR laserColor = al_map_rgb(255, 0, 0);

    float playerRot = this->Get_rotation();

    for (size_t i = 0; i < _offsets.size(); ++i) {
        float angle = playerRot + _offsets[i];

        float dist = _distances[i];

        float lineLength = (dist > 0) ? dist : 150.0f;

        float endX = this->position.x + cosf(-angle) * lineLength;
        float endY = this->position.y + sinf(-angle) * lineLength;

        al_draw_line(this->position.x, this->position.y, endX, endY, laserColor, 1.0f);
    }
}

void PlayerAI::update_distance_to_next_checkpoint()
{
	Utils::line nextCheckpoint = *_checkpoints[this->Get_current_check_point_index()];
    Utils::line points = _player_line.get_closest_points(nextCheckpoint);

    Utils::vec2 colVec = points.a - points.b;

    this->_checkpoint_distance=colVec.Length();
}

void PlayerAI::update_degree_to_next_checkpoint()
{
    Utils::line nextCheckpoint = *_checkpoints[this->Get_current_check_point_index()];
	Utils::vec2 v1 = _player_line.b - _player_line.a; // wektor kierunku gracza
    Utils::vec2 v2 = nextCheckpoint.b - nextCheckpoint.a; // wektor kierunku checkpointu

	float dot = v1.dot(v2);
	float det = v1.x * v2.y - v1.y * v2.x;

	_checkpoint_angle = atan2f(det, dot);

    //float angle_degrees = _degree_to_next_checkpoint * (180.0f / M_PI);
	//_degree_to_next_checkpoint = angle_degrees;
}



void PlayerAI::show_stats() const
{
    std::cout << "isHitting: " << this->touching_wall << " Obecny CP: " << this->Get_current_check_point_index() << " Dystans do CP: " << _checkpoint_distance << " | Kat: " << _checkpoint_angle << std::endl;

}

void PlayerAI::update_player_line()
{
        Utils::vec2 center = this->position;
        float angle = this->Get_rotation();

        float halfLength = this->bike_height / 2.0f;

        float dirX = cos(-angle);
        float dirY = sin(-angle);

        _player_line.a.x = center.x - (dirX * halfLength) * 1.7f;
        _player_line.a.y = center.y - (dirY * halfLength) * 1.7f;

        _player_line.b.x = center.x + (dirX * halfLength) * 1.7f;
        _player_line.b.y = center.y + (dirY * halfLength) * 1.7f;
}







