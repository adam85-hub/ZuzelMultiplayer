#include "OptionWithBinding.h"

OptionWithBinding::OptionWithBinding(std::string displayed_text, OptionWithValue* binded_to, int default_val, int min, int max) :
	OptionWithValue(displayed_text, default_val, min, max),
	_binded_option(binded_to)
{
	_binded_option->On_value_change([this](int old_val, int new_val) {
		if (_val + old_val >= _max) {
			_val = std::max(_max - new_val, 0);
			return;
		}
		});
}

void OptionWithBinding::Change_value(int change)
{
	int next_val = _val + change;

	if (next_val >= _min and next_val + _binded_option->Get_value() <= _max) {
		_val = next_val;
	}
}
