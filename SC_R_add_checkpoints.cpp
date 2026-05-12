#include "RaceScene.h"

void RaceScene::add_checkpoints(const std::string& str) {

	int num_points = 0;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == ',')
			num_points++;
	}

	//utworzenie tablicy punktow
	Utils::vec2* points = new Utils::vec2[num_points];

	int pos_in_str = 0, pos_digit_start;
	for (int i = 0; i < num_points; i++) {
		pos_digit_start = pos_in_str;

		while (str[pos_in_str] != ' ')pos_in_str++;

		points[i].x = std::stof(str.substr(pos_digit_start, pos_in_str - pos_digit_start).c_str());
		pos_digit_start = pos_in_str + 1;

		while (str[pos_in_str] != ',')pos_in_str++;

		points[i].y = std::stof(str.substr(pos_digit_start, pos_in_str - pos_digit_start).c_str());
		pos_in_str++;
	}

	//utworzenie linii
	_checkpoints_count = num_points / 2;

	_checkpoints = std::make_unique<Utils::line[]>(_checkpoints_count);


	for (int i = 0; i < _checkpoints_count; i++) {
		// i*2 oraz i*2 + 1 daj¹ pary: (0,1), (2,3), (4,5)...
		_checkpoints[i] = Utils::line(points[i * 2], points[i * 2 + 1]);
	}

	//!!!!!
	delete[] points;
}