#include "WallDetector.h"



WallDetector::WallDetector() {
    offsets = { -45.0f, -30.0f, -15.0f, 0.0f, 15.0f, 30.0f, 45.0f };
}

WallDetector::~WallDetector()
{
	for (auto* player : players) {
		delete player;
	}
	for (auto* wall : walls) {
		delete wall;
	}
}


void WallDetector::AddPlayer(Player* player)
{
	this->players.push_back(player);
}

void WallDetector::AddWall(Wall* wall)
{
	this->walls.push_back(wall);
}

float WallDetector::CalculateDistance(const Player* player, const Wall* wall, float angle)
{
    // U¿ywamy przekazanego 'angle', a nie player->GetRotation()
    Utils::vec2 dir = { cosf(-angle), sinf(-angle) };

    // 2. Pobierz wektor œciany
    Utils::vec2 start = wall->a;
    Utils::vec2 end = wall->b;
    Utils::vec2 wallVec = { end.x - start.x, end.y - start.y };

    // 3. Oblicz wyznacznik
    float det = dir.x * wallVec.y - dir.y * wallVec.x;

    // Jeœli det jest bliskie 0, promieñ i œciana s¹ równoleg³e
    if (std::abs(det) < 1e-6f) return -1.0f;

    // 4. Oblicz t oraz u
    Utils::vec2 diff = { start.x - player->position.x, start.y - player->position.y };

    float t = (diff.x * wallVec.y - diff.y * wallVec.x) / det;
    float u = (diff.x * dir.y - diff.y * dir.x) / det;

    // 5. Walidacja wyniku
    if (t > 0 && u >= 0.0f && u <= 1.0f) {
        return t; // Zwraca dystans
    }

    return -1.0f; // Brak trafienia
}

void WallDetector::Update() {
    
    for (Player* player : players) {
        for (int i = 0; i < offsets.size(); ++i) {
            // Zamiana stopni na radiany
            float rayAngle = player->GetRotation() + (offsets[i] * M_PI / 180.0f);

            float minDistance = std::numeric_limits<float>::max();
            bool hit = false;

            for (const auto& wall : walls) {

                float dist = CalculateDistance(player, wall, rayAngle);
				//mozn¹ zrobiæ optymalizacjê ¿e jak znajdzie chodŸ jedn¹ sciane i j¹ policzy to nie liczyæ innych

                if (dist > 0 && dist < minDistance) {
                    minDistance = dist;
                    hit = true;
                }
            }

            player->sensorDistances[i] = hit ? minDistance : -1.0f;
        }
    }
}

void WallDetector::DrawSensors() {
    ALLEGRO_COLOR laserColor = al_map_rgb(255, 0, 0);

    for (Player* player : players) {
        if (!player) continue;//nullptr

        float playerRot = player->GetRotation();

        for (int i = 0; i < offsets.size(); ++i) {
            // Obliczamy k¹t w radianach
            float angle = playerRot + (offsets[i] * M_PI / 180.0f);

            // Pobieramy wczeœniej obliczon¹ odleg³oœæ
            float dist = player->sensorDistances[i];

            // Jeœli nie ma trafienia (dist < 0), rysujemy liniê o sta³ej d³ugoœci (np. 150px)
            // Dziêki temu zobaczysz, ¿e "widok" gracza siê obraca, nawet gdy nie ma œcian
            float lineLength = (dist > 0) ? dist : 150.0f;

            // Obliczamy koniec linii
            float endX = player->position.x + cosf(-angle) * lineLength;
            float endY = player->position.y + sinf(-angle) * lineLength;

            al_draw_line(player->position.x, player->position.y, endX, endY, laserColor, 1.0f);
        }
    }
}