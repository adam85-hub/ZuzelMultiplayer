#include "RaceScene.h"
#include "LOG.h"

#include <fstream>
#include <filesystem>

void RaceScene::read_polygons_from_file() {
	constexpr std::string_view filepath = "./Assets/track_colliders.txt";
	std::ifstream file;
	file.open(filepath);
	if (!file.is_open())
		throw std::runtime_error("Couldnt open file: " + std::string(filepath));

	if (_inner_track_collider != nullptr)
		delete[] _inner_track_collider;
	if (_outer_track_collider != nullptr)
		delete[] _outer_track_collider;
	if (_start_line != nullptr)
		delete[] _start_line;

	std::string line;
	std::getline(file, line); // linia 1
	string_to_polygon(line, _inner_track_collider, _inner_track_collider_len);
	std::getline(file, line); // linia 2
	string_to_polygon(line, _outer_track_collider, _outer_track_collider_len);
	std::getline(file, line); //linia 3
	int discard; string_to_polygon(line, _start_line, discard);
}