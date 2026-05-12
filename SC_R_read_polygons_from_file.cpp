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

	if (_start_line != nullptr)
		delete[] _start_line;

	std::string line;

	//------- obsluga band -------
	std::vector <Utils::line> temp;

	std::getline(file, line); // linia 1
	add_barriers(line,temp);
	std::getline(file, line); // linia 2	
	add_barriers(line,temp);

	_barriers_count = static_cast<int>(temp.size());
	_barriers = std::make_unique<Utils::line[]>(_barriers_count);

	for (int i = 0; i < _barriers_count; i++) {
		_barriers[i] = temp[i];
	}
	temp.clear();


	//--- obsluga linii startowej ---
	std::getline(file, line); //linia 3
	int discard; string_to_polygon(line, _start_line, discard);


	//--- obsluga checkpointów ---
	std::getline(file, line); //linia 4
	add_checkpoints(line);
}