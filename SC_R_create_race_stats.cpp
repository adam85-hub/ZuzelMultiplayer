#include "RaceScene.h"

RaceStats* RaceScene::create_race_stats() const {
	RaceStats* stats = new RaceStats;

	stats->player_count = _number_of_players;
	stats->ai_count = _number_of_ais;
	stats->lap_count = _number_of_laps;

	stats->player_order = new int[_total_player_count];
	for (int i = 0; i < _total_player_count; i++)
		stats->player_order[i] = i;
	std::sort(stats->player_order, stats->player_order + _total_player_count, [this](int ai, int bi) {
		const Player* a = _players[ai];
		const Player* b = _players[bi];

		if (a->race_time == -1 || b->race_time == -1)
			throw std::exception("Can't create RaceStats while the race is still in progress!");

		return a->race_time < b->race_time;
	});

	stats->times = new double[_total_player_count];
	stats->is_ai = new bool[_total_player_count];
	for (int i = 0; i < _total_player_count; i++) {
		stats->times[i] = _players[i]->race_time;
		stats->is_ai[i] = _players[i]->Is_ai();
	}

	return stats;
}