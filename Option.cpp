#include "Option.h"

Option::Option(std::string displayed_text, std::function<void()> action) :
	_text(displayed_text),
	_action(action)
{
	
}

std::string Option::Get_display_text() const {
	return _text;
}

void Option::Invoke_action()
{
	_action();
}
