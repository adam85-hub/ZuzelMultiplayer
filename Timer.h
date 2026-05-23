#pragma once
#include <string>

class Timer
{
public:
	void Start();
	void Pause();
	void Unpause();

	double Get_time() const;
	std::string Get_time_str() const;

	static std::string Time_to_str(double time);
private:
	static std::string to_leading_0_str(int time);
	double get_current_pause_time() const;

	double _start_time = -1;
	double _pause_start_time = -1;
	double _pause_time = 0;
};

