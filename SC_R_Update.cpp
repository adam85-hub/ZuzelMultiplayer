#include "RaceScene.h"
#include "Consts.h"

void RaceScene::Update(KeyStatesTable key_states) {
	for (int i = 0; i < _number_of_players; i++) {
		bool is_turning = key_states[_turn_buttons[i]] & c_KEY_DOWN;
		_players[i]->Update(is_turning);
	}
}