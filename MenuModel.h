#pragma once
#include <string>
#include <vector>

#include "LOG.h"

// Zawiera logikê dzia³ania menu
class MenuModel {
public:
	MenuModel() : _number_of_players(2) {
	}

	void Get_menu_options(std::vector<std::string> &menu_options) {
		if (menu_options.size() < _number_of_options) {
			const int items_to_add = _number_of_options - menu_options.size();
			for (int i = 0; i <= items_to_add; i++)
				menu_options.push_back("");
		}
		menu_options[0] = "Rozpocznij grê";
		menu_options[1] = "Liczba graczy < " + std::to_string(_number_of_players) + " >";
		menu_options[2] = "WyjdŸ";
	}
	
	void Next_menu_option() {
		if (_selected_option < _number_of_options - 1)
			_selected_option++;
	}

	void Previous_menu_option() {
		if (_selected_option > 0)
			_selected_option--;
	}

	int Get_selected_option_index() {
		return _selected_option;
	}
	
	// Zmienia opcjê o dan¹ zmianê
	void Change_value_of_option(short change) {
		if (_selected_option == 1) {
			if (_number_of_players + change >= 1 and _number_of_players + change <= 4) {
				_number_of_players += change;
			}
		}
	}

private:
	const short _number_of_options = 3;
	short _selected_option = 0;
	short _number_of_players;
public:
	const short& number_of_players = _number_of_players;
};
