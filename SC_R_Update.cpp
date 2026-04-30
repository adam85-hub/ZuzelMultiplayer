#include "RaceScene.h"
#include "Consts.h"

void RaceScene::Update(KeyStatesTable key_states) {
	// restart wyœcigu:
	if (key_states[ALLEGRO_KEY_R] & c_KEY_PRESSED) {
		_game_commands->switch_scene.Execute(new RaceScene(_game_commands, _number_of_players));
	}

	for (int i = 0; i < _number_of_players; i++) {
		bool is_turning = key_states[_turn_buttons[i]] & c_KEY_DOWN;
		_players[i]->Update(is_turning);
	}

	//--- COLLISION/CHECKPOINT ACTION---
	_collision_manager.Update();
	//--- UPDATE SENSORS ---
	_wall_detector.Update();
	//--- UPDATE SCORE TABLE ---
	_score_table.updateTable();
}