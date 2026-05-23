#include "Timer.h"
#include <allegro5/allegro5.h>

void Timer::Start() {
	_start_time = al_get_time();
}

double Timer::Get_time() const {
	if (_start_time == -1)
		return 0;

	return al_get_time() - _start_time - get_current_pause_time();
}

std::string Timer::to_leading_0_str(int time) {
	std::string str = std::to_string(time);
	if (time < 10)
		str = "0" + str;
	return str;
}

std::string Timer::Time_to_str(double time) {
	int minutes, seconds, hundreths;

	minutes = (int)time / 60;
	time -= minutes * 60;
	seconds = (int)time;
	time -= seconds;
	hundreths = (int)(100 * time);

	return to_leading_0_str(minutes) + ":" + to_leading_0_str(seconds) + ":" + to_leading_0_str(hundreths);
}

std::string Timer::Get_time_str() const {
	return Time_to_str(Get_time());
}

void Timer::Pause() {
	if (_start_time == -1)
		return;

	_pause_start_time = al_get_time();
}

void Timer::Unpause() {
	if (_start_time == -1)
		return;

	_pause_time += al_get_time() - _pause_start_time;
	_pause_start_time = -1;
}

double Timer::get_current_pause_time() const {
	if (_pause_start_time == -1)
		return _pause_time;

	return _pause_time + al_get_time() - _pause_start_time;
}