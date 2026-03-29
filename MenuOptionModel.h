#pragma once
#include <string>

using GenerateDisplayNameFn = std::string(*)();

class MenuOptionModel {
public:
	MenuOptionModel(GenerateDisplayNameFn generate_display_name_fn) {
		_generate_display_name_fn = generate_display_name_fn;
	}

	std::string GetDisplayName() {

	}
private:
	GenerateDisplayNameFn _generate_display_name_fn;
};
