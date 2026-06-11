#pragma once

struct RaceStats {
	short player_count;
	int lap_count;
	double* times = nullptr;
	int* player_order = nullptr;

	~RaceStats() {
		if(times != nullptr)
			delete[] times;
		if(player_order != nullptr)
			delete[] player_order;
	}
};