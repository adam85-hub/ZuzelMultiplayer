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
}

EndScene::~EndScene() {
	al_destroy_font(_font_title);
	delete _race_stats;
}

void EndScene::Update(KeyStatesTable key_states) {

}

void EndScene::Render() {
	Utils::draw_polish_text(_font_title, al_map_rgb(255, 255, 255), c_RENDER_WIDTH / 2, _results_table.Get_top_left().y - _title_height - 20,
		ALLEGRO_ALIGN_CENTER, "Koniec gry");

	_results_table.Render();
}