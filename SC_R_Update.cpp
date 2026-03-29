#include "RaceScene.h"

void RaceScene::Update(KeyStatesTable key_states) {
	for (int i = 0; i < _number_of_players; i++) {
		_players[i]->Update();
	}
}