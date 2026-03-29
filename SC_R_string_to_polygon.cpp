#include "RaceScene.h"

void RaceScene::string_to_polygon(std::string str, Utils::vec2*& out, int& out_len) {
	out_len = 0;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == ',')
			out_len++;
	}

	out = new Utils::vec2[out_len];

	int pos_in_str = 0, pos_digit_start;
	for (int i = 0; i < out_len; i++) {
		pos_digit_start = pos_in_str;
		while (str[pos_in_str] != ' ')
			pos_in_str++;
		out[i].x = std::stof(str.substr(pos_digit_start, pos_in_str - pos_digit_start).c_str());
		pos_digit_start = pos_in_str + 1;
		while (str[pos_in_str] != ',')
			pos_in_str++;
		out[i].y = std::stof(str.substr(pos_digit_start, pos_in_str - pos_digit_start).c_str());
		pos_in_str++;
	}
}