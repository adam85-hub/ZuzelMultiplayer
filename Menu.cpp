#include "Menu.h"
#include <allegro5/allegro_ttf.h>
#include "draw_polish_text.h"

Menu::Menu(Utils::vec2 top_left, bool centered, int font_size, int line_margin) :
	_top_left(top_left),
	_line_margin(line_margin),
	_centered(centered)
{
	_font = al_load_ttf_font(c_MAIN_FONT_PATH, font_size, 0);
	_line_height = al_get_font_line_height(_font);
}

Menu::~Menu() {
	al_destroy_font(_font);

	for (Option* option : _options)
		delete option;
}

void Menu::Update(KeyStatesTable key_states) {
	if (key_states[ALLEGRO_KEY_UP] & c_KEY_PRESSED and _selected_option > 0)
		_selected_option--;
	else if (key_states[ALLEGRO_KEY_DOWN] & c_KEY_PRESSED and _selected_option < _options.size()-1)
		_selected_option++;
	
	if (key_states[ALLEGRO_KEY_LEFT] & c_KEY_PRESSED)
		_options[_selected_option]->Change_value(-1);
	else if (key_states[ALLEGRO_KEY_RIGHT] & c_KEY_PRESSED)
		_options[_selected_option]->Change_value(1);

	if (key_states[ALLEGRO_KEY_ENTER] & c_KEY_PRESSED)
		_options[_selected_option]->Invoke_action();
}

void Menu::Render() const {
	for (int i = 0; i < _options.size(); i++) {
		ALLEGRO_COLOR color = i == _selected_option ? c_SELECTED_OPTION : c_WHITE;
		Utils::draw_polish_text(_font, color, _top_left.x, _top_left.y +_line_height * i,
			_centered * ALLEGRO_ALIGN_CENTER, _options[i]->Get_display_text());
	}
}

void Menu::Add_option(Option* option) {
	_options.push_back(option);
}

int Menu::Get_option_value(int index)
{
	return _options.at(index)->Get_value();
}

