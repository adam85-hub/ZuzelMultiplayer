#pragma once
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <array>

#include "Player.h"
#include "ResourceManager.h"
#include "Timer.h"

class ScoreTable
{
public:
	ScoreTable(Player** players, short players_count, Timer* race_timer);
	~ScoreTable();
	void Update();
	void Render() const;
private:
	void sort_players();

	const Player *const *const _players; // sta³a tablica
	short* _player_order;
	int _players_count;
	std::vector<std::string> _columns = {"Miejsce", "Gracz", "Liczba okr¹¿eñ", "Czas"};
	Timer* _race_timer;
	
	Utils::ResourceManager _resource_manager;
	ALLEGRO_FONT* _font_table;

	std::vector<float> _column_width;
	Utils::vec2 _size;
	Utils::vec2 _left_top;
	const float _margin_col = 50;
	const float _margin_row = 10;
	float _row_height;
};
