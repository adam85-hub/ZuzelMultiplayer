#pragma once
#include "OptionWithValue.h"

class OptionWithBinding : public OptionWithValue
{
public:
	OptionWithBinding(std::string displayed_text, OptionWithValue* binded_to, int default_val, int min, int max);

	void Change_value(int change) override;
private:
	OptionWithValue* _binded_option;
};

