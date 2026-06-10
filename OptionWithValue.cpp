#include "OptionWithValue.h"

OptionWithValue::OptionWithValue(std::string displayed_text, int default_val, int min, int max) :
	Option(displayed_text, []() {}),
	_val(default_val),
	_min(min),
	_max(max)
{
	if (default_val < min or default_val > max)
		throw std::exception("Default option value must be between min and max");
}

void OptionWithValue::Change_value(int change) {
	int next_val = _val + change;

	if (next_val >= _min and next_val <= _max)
		_val = next_val;
}

std::string OptionWithValue::Get_display_text() const {
	return _text + " < " + std::to_string(_val) + " >";
}

int OptionWithValue::Get_value() {
	return _val;
}
