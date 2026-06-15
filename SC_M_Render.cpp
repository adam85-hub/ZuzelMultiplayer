#include "MenuScene.h"
#include "Consts.h"
#include "draw_polish_text.h"

void MenuScene::Render() {
	Utils::draw_polish_text(_font_title, _color_text_default, _left_top.x, _left_top.y, 0, "¯u¿el Multiplayer");

	_menu->Render();
}