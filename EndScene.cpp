#include "EndScene.h"
#include "draw_polish_text.h"
#include <allegro5/allegro_ttf.h>

EndScene::EndScene(GameCommands* gameCommands) : Scene(gameCommands) {
	_font_title = al_load_ttf_font(c_MAIN_FONT_PATH, c_RENDER_HEIGHT / 5, 0);
}

EndScene::~EndScene() {
	al_destroy_font(_font_title);
}

void EndScene::Update(KeyStatesTable key_states) {

}

void EndScene::Render() {
	Utils::draw_polish_text(_font_title, al_map_rgb(255, 255, 255), c_RENDER_WIDTH / 2, c_RENDER_HEIGHT / 2, Utils::ALIGN_CENTER_XY, "Koniec gry");
}