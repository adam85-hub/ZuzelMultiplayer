#include "EndScene.h"
#include "draw_polish_text.h"
#include <allegro5/allegro_ttf.h>
#include "MenuScene.h"
#include "RaceScene.h"

EndScene::EndScene(GameCommands* game_commands, RaceStats* race_stats) : 
	Scene(game_commands),
	_results_table(race_stats),
	_race_stats(race_stats)
{
	_font_title = al_load_ttf_font(c_MAIN_FONT_PATH, c_RENDER_HEIGHT / 5, 0);
	_title_height = al_get_font_line_height(_font_title);

	_menu = std::make_unique<Menu>(Utils::vec2(c_RENDER_WIDTH/2, _results_table.Get_bottom_right().y + c_RENDER_HEIGHT/18));

	_menu->Add_option(new Option("Zagraj ponownie", [this]() {
		_game_commands->switch_scene.Execute(new RaceScene(_game_commands, _race_stats->player_count, _race_stats->lap_count));
		}));
	_menu->Add_option(new Option("Powrót do menu", [this]() {
		_game_commands->switch_scene.Execute(new MenuScene(_game_commands));
		}));
	_menu->Add_option(new Option("WyjdŸ z gry", [this]() {
		_game_commands->exit.Execute(true);
		}));
}

EndScene::~EndScene() {
	al_destroy_font(_font_title);
	delete _race_stats;
}

void EndScene::Update(KeyStatesTable key_states) {
	_menu->Update(key_states);
}

void EndScene::Render() {
	static const ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);

	Utils::draw_polish_text(_font_title, white, c_RENDER_WIDTH / 2, _results_table.Get_top_left().y - _title_height - 20,
		ALLEGRO_ALIGN_CENTER, "Koniec gry");

	_results_table.Render();

	_menu->Render();
}