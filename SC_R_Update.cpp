#include "RaceScene.h"
#include "Consts.h"
#include "CollisionDetector.h"



void RaceScene::Update(KeyStatesTable key_states) {
	// restart wyœcigu:
	if (key_states[ALLEGRO_KEY_R] & c_KEY_PRESSED) {
		_game_commands->switch_scene.Execute(new RaceScene(_game_commands, _number_of_players));
	}
	


	// LOGIKA TESTU: Tylko ustawiamy flagê
	if (key_states[ALLEGRO_KEY_T] & c_KEY_DOWN) {
		_test_collision_active = true;
	}
	else {
		_test_collision_active = false;
	}



	for (int i = 0; i < _number_of_players; i++) {
		bool is_turning = key_states[_turn_buttons[i]] & c_KEY_DOWN;
		_players[i]->Update(is_turning);
	}

	if (key_states[ALLEGRO_KEY_R] & c_KEY_PRESSED) {
		_game_commands->switch_scene.Execute(new RaceScene(_game_commands, _number_of_players));
	}

	// w tym miejscu funkcja do obs³ugi kolizji Fabiana
		//al_draw_text(font, al_map_rgb(255, 0, 0), 10, 10, 0, "KOLIZJA: TAK");

}