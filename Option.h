#pragma once
#include <string>
#include <functional>

class Option
{
public:
	Option(std::string displayed_text, std::function<void()> action);
	virtual ~Option() {};

	virtual void Change_value(int) {};
	virtual int Get_value() { return -1; };

	virtual std::string Get_display_text() const;

	void Invoke_action();
protected:
	const std::string _text;

	const std::function<void()> _action;
};

