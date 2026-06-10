#include "PlayerAI.h"
#include <iostream>


Utils::line* PlayerAI::_barriers = nullptr;
int PlayerAI::_barriers_count = 0;

Utils::line* PlayerAI::_checkpoints = nullptr;
int PlayerAI::_checkpoints_count = 0;

const std::array<float, 8> PlayerAI::_offsets = { -1.5f, -0.5f, -0.25f, 0.0f, 0.25f, 0.50f, 1.5f ,2.4f};

void PlayerAI::Set_walls(Utils::line* barriers_ptr, int count)
{
    _barriers = barriers_ptr;
    _barriers_count = count;
}

void PlayerAI::Set_checkpoints(Utils::line* checkpoints_ptr, int count)
{
    _checkpoints = checkpoints_ptr;
    _checkpoints_count = count;
}

std::shared_ptr<SpeedwayState> PlayerAI::Get_player_state() const {
    std::array<double, 8> distances;
    for (size_t i{}; i < 8; i++) {
        distances[i] = static_cast<double>(_distances[i]);
    }
    return std::make_shared<SpeedwayState>(
        distances, 
        calculate_velocity_components(), 
        Get_rotation(), 
        _checkpoint_distance, 
        _checkpoint_angle, 
        _player_distance, 
        _player_angle, 
        touching_wall, 
        _is_hitting_player, 
        _is_hitting_checkpoint
    );
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

    return 0.0f; 
}

// --- Update ---
void PlayerAI::update_sensors() {
    float playerRot = this->Get_rotation();

    for (size_t i = 0; i < _offsets.size(); ++i) {
        float rayAngle = playerRot + _offsets[i];

        float minDistance = std::numeric_limits<float>::max();
        bool hit = false;

        for (int i = 0; i < _barriers_count; ++i) {

            float dist = calculate_distance(&_barriers[i], rayAngle);

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
    this->update_distance_to_next_checkpoint();
	this->update_degree_to_next_checkpoint();
};

void PlayerAI::Render() const {
    Player::Render();
    this->draw_sensors();
    //this->show_stats();
}

std::array<double, 2> PlayerAI::calculate_velocity_components() const {
    float angle = Get_rotation();

    float dirX = cosf(-angle);
    float dirY = sinf(-angle);

    float vel = Get_velocity();
    
    return { vel * dirX, vel * dirY };
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
	Utils::line nextCheckpoint = _checkpoints[this->Get_current_checkpoint_index()];
    Utils::line points = this->line_postion.get_closest_points(nextCheckpoint);

    Utils::vec2 colVec = points.a - points.b;

    this->_checkpoint_distance=colVec.Length();
}

void PlayerAI::update_degree_to_next_checkpoint()
{
    Utils::line nextCheckpoint = _checkpoints[this->Get_current_checkpoint_index()];
	Utils::vec2 v1 = line_postion.b - line_postion.a; // wektor kierunku gracza
    Utils::vec2 v2 = nextCheckpoint.b - nextCheckpoint.a; // wektor kierunku checkpointu

	float dot = v1.dot(v2);
	float det = v1.x * v2.y - v1.y * v2.x;

	_checkpoint_angle = atan2f(det, dot);

    //float angle_degrees = _degree_to_next_checkpoint * (180.0f / M_PI);
	//_degree_to_next_checkpoint = angle_degrees;
}

void PlayerAI::show_stats() const
{
    std::cout << "Player distance " << this-> _player_distance << " Wall: " << this->touching_wall << " Player: " << this->_is_hitting_player << " CP_hit: " << this->_is_hitting_checkpoint << " CP: " << this->Get_current_checkpoint_index() << " Dystans do CP: " << _checkpoint_distance << " | CP Kat: " << _checkpoint_angle << std::endl;

}








