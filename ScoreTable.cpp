#include "ScoreTable.h"

#include <algorithm>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "Consts.h"
#include "draw_polish_text.h"
#include "vec2.h"
#include "check_functions.h"

ScoreTable::ScoreTable(Player** players, short player_count, short number_of_laps, Timer* race_timer) :
	Table(c_MIDDLE, { "Miejsce", "", "Gracz", "Okr¹¿enie", "Czas"}, player_count),
	_players(players),
	_players_count(player_count),
	_race_timer(race_timer),
	_number_of_laps(number_of_laps)
{
	_player_order = new short[player_count];
	short ai_count = 0;
	for (short i = 0; i < player_count; i++) {
		_player_order[i] = i;

		if (_players[i]->Is_ai())
			ai_count++;
	}


	constexpr const char* bmp_path = "./Assets/robot.bmp";
	_robot_bitmap = al_load_bitmap(bmp_path);
	Utils::check_resource_loaded(_robot_bitmap, bmp_path);
	al_convert_mask_to_alpha(_robot_bitmap, al_map_rgb(0, 0, 0));

	_column_width[1] = ai_count == 0 ? 0 : al_get_bitmap_width(_robot_bitmap);
	_column_width[2] = Utils::get_polish_text_width(_font_table, "Czerwony"); // najszerszy napis
	_column_width[4] = Utils::get_polish_text_width(_font_table, "22:22:22");

	calculate_size();
}

ScoreTable::~ScoreTable()
{
	delete[] _player_order;
	al_destroy_bitmap(_robot_bitmap);
}

void ScoreTable::sort_players() {
	std::sort(_player_order, _player_order + _players_count, [this](short ai, short bi) {
		const Player* a = _players[ai];
		const Player* b = _players[bi];

		if (a->Has_finished() and b->Has_finished())
			return a->race_time < b->race_time;

		if (a->Has_finished())
			return true;
		else if (b->Has_finished())
			return false;

		if (a->Get_laps() != b->Get_laps()) {
			return a->Get_laps() > b->Get_laps();
		}

		return a->Get_current_checkpoint_index() > b->Get_current_checkpoint_index();
	});
}

void ScoreTable::Update() {
	sort_players();
	_players_finished = 0;
	for (int i = 0; i < _players_count; i++) {
		if (_players[i]->Has_finished()) _players_finished++;
	}
}

void ScoreTable::Render() const {
	static const ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
	static const ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
	static const ALLEGRO_COLOR bg_color = al_map_rgba(49, 50, 50, 200);
	static const ALLEGRO_COLOR grey = al_map_rgb(180, 180, 180);

	// t³o:
	al_draw_filled_rectangle(_left_top.x - _table_padding_x, _left_top.y - _table_padding_y, 
		_left_top.x + _size.x + _table_padding_x, _left_top.y + _size.y + _table_padding_y, bg_color);
	al_draw_rectangle(_left_top.x - _table_padding_x, _left_top.y - _table_padding_y,
		_left_top.x + _size.x + _table_padding_x, _left_top.y + _size.y + _table_padding_y, black, 15);

	draw_title_row();
	
	// zawartoœæ tabeli:
	float advance = 0;
	for (int i = 0; i < _players_count; i++) {
		float y = _left_top.y + (_row_height + _margin_row) * (i + 1);
		short p_index = _player_order[i];

		Utils::draw_polish_text(_font_table, white, _left_top.x, y, 0, std::to_string(i + 1));

		advance = _column_width[0] + _margin_col;
		if(_players[p_index]->Is_ai())
			al_draw_bitmap(_robot_bitmap, _left_top.x + advance, y, 0);

		advance += _column_width[1] + _margin_col;
		Utils::draw_polish_text(_font_table, c_PLAYER_COLOR[p_index], _left_top.x + advance, y, 0, c_PLAYER_NAME[p_index]);

		advance += _column_width[2] + _margin_col;
		if (_players[p_index]->Has_finished())
			Utils::draw_polish_text(_font_table, grey, _left_top.x + advance, y, 0, "Koniec");
		else
			Utils::draw_polish_text(_font_table, white, _left_top.x + advance, y, 0, 
				std::to_string(_players[p_index]->Get_laps_to_display()) + " / " + std::to_string(_number_of_laps));

		advance += _column_width[3] + _margin_col;
		if(_players[p_index]->Has_finished())
			Utils::draw_polish_text(_font_table, white, _left_top.x + advance, y, 0, Timer::Time_to_str(_players[p_index]->race_time));
		else if (i == _players_finished) {
			Utils::draw_polish_text(_font_table, white, _left_top.x + advance, y, 0, _race_timer->Get_time_str());
		}
	}
}