#include "EndScene.h"
#include "draw_polish_text.h"
#include <allegro5/allegro_ttf.h>

EndScene::EndScene(GameCommands* game_commands, RaceStats* race_stats) : 
	Scene(game_commands),
	_results_table(race_stats),
	_race_stats(race_stats)
{
	_font_title = al_load_ttf_font(c_MAIN_FONT_PATH, c_RENDER_HEIGHT / 5, 0);
	_title_height = al_get_font_line_height(_font_title);
	_font_menu = al_load_ttf_font(c_MAIN_FONT_PATH, c_RENDER_HEIGHT / 20, 0);
	_menu_line_height = al_get_font_line_height(_font_menu) + 20;
}

EndScene::~EndScene() {
	al_destroy_font(_font_title);
	al_destroy_font(_font_menu);
	delete _race_stats;
}

void EndScene::Update(KeyStatesTable key_states) {

}

void EndScene::Render() {
	static const ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);

	Utils::draw_polish_text(_font_title, white, c_RENDER_WIDTH / 2, _results_table.Get_top_left().y - _title_height - 20,
		ALLEGRO_ALIGN_CENTER, "Koniec gry");

	_results_table.Render();

	float menu_top = _results_table.Get_bottom_right().y + 40.f;

	for (int i = 0; i < _option_count; i++) {
		ALLEGRO_COLOR color = i == _selected_option ? c_SELECTED_OPTION : white;
		Utils::draw_polish_text(_font_menu, color, c_RENDER_WIDTH / 2, menu_top + _menu_line_height * i,
			ALLEGRO_ALIGN_CENTER, _options[i]);
	}
}