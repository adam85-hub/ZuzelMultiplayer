#include "MenuScene.h"
#include "Consts.h"

MenuScene::MenuScene(GameCommands* gameCommands) : SceneWithCommands(gameCommands) {
	_font_title = al_load_ttf_font(c_MAIN_FONT_PATH, c_RENDER_HEIGHT/10, 0);
	_resource_manager.Track_resource(_font_title);

	_font_menu_options = al_load_ttf_font(c_MAIN_FONT_PATH, c_RENDER_HEIGHT/20, 0);
	_resource_manager.Track_resource(_font_menu_options);

	_title_height = al_get_font_line_height(_font_title);
	_menu_option_height = al_get_font_line_height(_font_menu_options);

	_menu_model = std::make_unique<MenuModel>();
}