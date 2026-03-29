#include "MenuScene.h"
#include "NotImplementedException.h"
#include "RaceScene.h"

void MenuScene::Update(KeyStatesTable key_states) {
	if (key_states[ALLEGRO_KEY_DOWN] & c_KEY_PRESSED)
		_menu_model->Next_menu_option();
	if (key_states[ALLEGRO_KEY_UP] & c_KEY_PRESSED)
		_menu_model->Previous_menu_option();
	if (key_states[ALLEGRO_KEY_LEFT] & c_KEY_PRESSED)
		_menu_model->Change_value_of_option(-1);
	if (key_states[ALLEGRO_KEY_RIGHT] & c_KEY_PRESSED)
		_menu_model->Change_value_of_option(1);
	if (key_states[ALLEGRO_KEY_ENTER] & c_KEY_PRESSED) {
		switch (_menu_model->Get_selected_option_index()) {
			case 0:
				_game_commands->switch_scene.Execute(new RaceScene(_game_commands, _menu_model->number_of_players));
				break;
			case 2:
				_game_commands->exit.Execute(true);
				break;
		}
	}
}