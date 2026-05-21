#include "GameManager.h"
#include "ScoreTable.h"

void GameManager::render() {
	al_clear_to_color(al_map_rgb(0, 0, 0));
	_game->Render(); // rysuje nastêpn¹ klatkê
	al_flip_display(); // wyœwietla zmiany na ekranie
}