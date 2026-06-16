#include "MenuScene.h"
#include "Consts.h"
#include "RaceScene.h"
#include "OptionWithValue.h"
#include "OptionWithBinding.h"

MenuScene::MenuScene(GameCommands* gameCommands) : 
	Scene(gameCommands),
	_left_top(c_RENDER_WIDTH/5, c_RENDER_HEIGHT/5)
{
	_font_title = al_load_ttf_font(c_MAIN_FONT_PATH, c_RENDER_HEIGHT/10, 0);
	_resource_manager.Track_resource(_font_title);
	_title_height = al_get_font_line_height(_font_title);

	_menu = std::make_unique<Menu>(_left_top + Utils::vec2(0, _title_height), false);

	OptionWithValue* number_of_players = new OptionWithValue("Liczba graczy", 2, 1, 4);

	_menu->Add_option(new Option("Rozpocznij grê", [this]() {
		_game_commands->switch_scene.Execute(new RaceScene(_game_commands, 
			_menu->Get_option_value(1), _menu->Get_option_value(2), _menu->Get_option_value(3)));
		}));
	_menu->Add_option(number_of_players);
	_menu->Add_option(new OptionWithBinding("Liczba AI", number_of_players, 2, 0, 4));
	_menu->Add_option(new OptionWithValue("Liczba okr¹¿eñ", 3, 1, 10));
	_menu->Add_option(new Option("WyjdŸ", [this]() {
		_game_commands->exit.Execute(true);
		}));
}