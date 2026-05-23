#include "PauseScene.h"
#include "draw_polish_text.h"
#include "Consts.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_primitives.h"

PauseScene::PauseScene(GameCommands* gameCommands) : Scene(gameCommands)
{
	_font_title = al_load_ttf_font(c_MAIN_FONT_PATH, c_RENDER_HEIGHT / 10, 0);
	_resource_manager.Track_resource(_font_title);
}

void PauseScene::Update(KeyStatesTable key_states) {

}

void PauseScene::Render() {
	al_draw_filled_rectangle(0, 0, c_RENDER_WIDTH, c_RENDER_HEIGHT, _color_background); // t³o

	Utils::draw_polish_text(_font_title, _color_text_default, c_RENDER_WIDTH / 2, c_RENDER_HEIGHT / 2, Utils::ALIGN_CENTER_XY, "Pauza!");
}