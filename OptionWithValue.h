#pragma once
#include "Option.h"
#include <functional>

class OptionWithValue : public Option
{
public:
	OptionWithValue(std::string displayed_text, int default_val, int min = 1, int max = 4);

	virtual void Change_value(int change) override;
	std::string Get_display_text() const override;
	int Get_value() override;

	void On_value_change(std::function<void(int, int)>);
protected:
	int _val;
	const int _min;
	const int _max;
private:
	std::function<void(int, int)> _on_change = nullptr;
};

