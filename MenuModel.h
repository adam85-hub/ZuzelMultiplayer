#pragma once
#include <string>
#include <vector>

#include "LOG.h"

// Zawiera logikê dzia³ania menu
class MenuModel {
public:
	MenuModel() : _number_of_players(2), _number_of_laps(3) {
	}

	void Get_menu_options(std::vector<std::string> &menu_options) {
		if (menu_options.size() < _number_of_options) {
			const int items_to_add = _number_of_options - menu_options.size();
			for (int i = 0; i <= items_to_add; i++)
				menu_options.push_back("");
		}
		menu_options[0] = "Rozpocznij grê";
		menu_options[1] = "Liczba graczy < " + std::to_string(_number_of_players) + " >";
		menu_options[2] = "Liczba okr¹¿eñ < " + std::to_string(_number_of_laps) + " >";
		menu_options[3] = "WyjdŸ";
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
			short after = _number_of_players + change;
			if (after >= 1 and after <= 4)
				_number_of_players = after;
		}
		else if (_selected_option == 2) {
			short after = _number_of_laps + change;
			if (after >= 1 and after <= 10)
				_number_of_laps = after;
		}
	}

private:
	const short _number_of_options = 4;
	short _selected_option = 0;
	short _number_of_players;
	short _number_of_laps;
public:
	const short& number_of_players = _number_of_players;
	const short& number_of_laps = _number_of_laps;
};
