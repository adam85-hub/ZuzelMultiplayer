#include "PauseScene.h"
#include "draw_polish_text.h"
#include "Consts.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_primitives.h"
#include "MenuScene.h"
#include "RaceScene.h"

PauseScene::PauseScene(GameCommands* gameCommands, Utils::Command<bool>* unpause_cmd, int player_count, int lap_count) : 
	Scene(gameCommands),
	_unpause_cmd(unpause_cmd)
{
	_font_title = al_load_ttf_font(c_MAIN_FONT_PATH, c_RENDER_HEIGHT / 8, 0);
	_resource_manager.Track_resource(_font_title);

	_menu = std::make_unique<Menu>(Utils::vec2(c_RENDER_WIDTH/2, _title_top + al_get_font_line_height(_font_title) + 10));

	_menu->Add_option(new Option("Wznów wyœcig", [this]() {
		_unpause_cmd->Execute(true);
		}));
	_menu->Add_option(new Option("Restartuj wyœcig", [this, player_count, lap_count]() {
		_game_commands->switch_scene.Execute(new RaceScene(_game_commands, player_count, lap_count));
		}));
	_menu->Add_option(new Option("Powrót do menu", [this]() {
		_game_commands->switch_scene.Execute(new MenuScene(_game_commands));
		}));
	_menu->Add_option(new Option("WyjdŸ z gry", [this]() {
		_game_commands->exit.Execute(true);
		}));
}

PauseScene::~PauseScene() {
	
}

void PauseScene::Update(KeyStatesTable key_states) {
	if (key_states[ALLEGRO_KEY_P] & c_KEY_PRESSED) {
		_unpause_cmd->Execute(true);
	}

	_menu->Update(key_states);
}

void PauseScene::Render() {
	al_draw_filled_rectangle(0, 0, c_RENDER_WIDTH, c_RENDER_HEIGHT, _color_background); // t³o

	Utils::draw_polish_text(_font_title, _color_text_default, c_RENDER_WIDTH / 2, _title_top, ALLEGRO_ALIGN_CENTRE, "Pauza!");

	_menu->Render();
}