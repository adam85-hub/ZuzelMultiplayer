#include "MenuScene.h"
#include "Consts.h"
#include "draw_polish_text.h"

#define MENU_LEFT c_RENDER_WIDTH/5
#define MENU_TOP c_RENDER_HEIGHT/5

void MenuScene::Render() {
	Utils::draw_polish_text(_font_title, _color_text_default, MENU_LEFT, MENU_TOP, 0, "¯u¿el Multiplayer");

	_menu_model->Get_menu_options(_menu_options);
	ALLEGRO_COLOR text_color = _color_text_default;
	const int selected_index = _menu_model->Get_selected_option_index();
	for (int i = 0; i < _menu_options.size(); i++) {
		if (i == selected_index)
			text_color = _color_text_selected;
		else
			text_color = _color_text_default;

		Utils::draw_polish_text(_font_menu_options, text_color, MENU_LEFT, MENU_TOP + _title_height + _menu_option_height*i,
			0, _menu_options[i]);
	}
}