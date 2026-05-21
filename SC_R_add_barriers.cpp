#include "RaceScene.h"

void RaceScene::add_barriers(const std::string& str, std::vector<Utils::line>& temp) {

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
	for (int i = 0; i < num_points-1; i++) {
		temp.emplace_back(points[i], points[i+1]);
	}
	temp.emplace_back(points[num_points - 1], points[0]);

	//!!!!!
	delete[] points;
}