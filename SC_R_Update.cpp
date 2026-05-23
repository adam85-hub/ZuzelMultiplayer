#include "RaceScene.h"
#include "Consts.h"

void RaceScene::Update(KeyStatesTable key_states) {
	if (_paused) {
		_pause_scene.Update(key_states);
		return;
	}

	// restart wyœcigu:
	if (key_states[ALLEGRO_KEY_R] & c_KEY_PRESSED) {
		_game_commands->switch_scene.Execute(new RaceScene(_game_commands, _number_of_players));
	}
	else if (key_states[ALLEGRO_KEY_P] & c_KEY_PRESSED) {
		pause();
	}
	
	_start_countdown.Update();
	if (!_start_countdown.Has_race_started())
		return;
	// po starcie wyścigu:

	for (int i = 0; i < _number_of_players; i++) {
		bool is_turning = key_states[_turn_buttons[i]] & c_KEY_DOWN;
		_players[i]->Update(is_turning);
	}

	//--- COLLISION/CHECKPOINT ACTION---
	_collision_manager.Update();
}