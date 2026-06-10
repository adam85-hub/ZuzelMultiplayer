#pragma once
#include "Option.h"

class OptionWithValue : public Option
{
public:
	OptionWithValue(std::string displayed_text, int default_val = -1, int min = 1, int max = 4);

	void Change_value(int change) override;
	std::string Get_display_text() const override;
	int Get_value() override;
private:
	int _val;
	const int _min;
	const int _max;
};

