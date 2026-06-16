#pragma once

struct RaceStats {
	short player_count;
	short ai_count;
	int lap_count;
	double* times = nullptr;
	int* player_order = nullptr;
	bool* is_ai = nullptr;

	~RaceStats() {
		if(times != nullptr)
			delete[] times;
		if(player_order != nullptr)
			delete[] player_order;
		if (is_ai != nullptr)
			delete[] is_ai;
	}
};