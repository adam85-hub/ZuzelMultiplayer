#pragma once
#include <string>

class Timer
{
public:
	void Start();

	double Get_time() const;
	std::string Get_time_str() const;

	static std::string Time_to_str(double time);
private:
	static std::string to_leading_0_str(int time);

	double _start_time = -1;
};

