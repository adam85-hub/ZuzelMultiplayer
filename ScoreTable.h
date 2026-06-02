#pragma once
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

#include "Table.h"
#include "Player.h"
#include "ResourceManager.h"
#include "Timer.h"

class ScoreTable : public Table
{
public:
	ScoreTable(Player** players, short players_count, short number_of_laps, Timer* race_timer);
	~ScoreTable();
	void Update();
	void Render() const;
private:
	void sort_players();

	const Player *const *const _players; // sta³a tablica
	short* _player_order;
	int _players_count;
	int _players_finished = 0;
	const short _number_of_laps;
	Timer* _race_timer;
};
