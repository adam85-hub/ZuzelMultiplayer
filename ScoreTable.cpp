#include "ScoreTable.h"

#include <algorithm>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "Consts.h"
#include "draw_polish_text.h"
#include "vec2.h"

ScoreTable::ScoreTable(Player** players, short players_count, Timer* race_timer) :
	_players(players),
	_players_count(players_count),
	_race_timer(race_timer)
{
	_font_table = al_load_ttf_font(c_MAIN_FONT_PATH, c_RENDER_HEIGHT / 20, 0);
	_resource_manager.Track_resource(_font_table);

	_player_order = new short[players_count];
	for (short i = 0; i < players_count; i++)
		_player_order[i] = i;

	// wymiary:
	_row_height = al_get_font_line_height(_font_table);

	for (std::string column : _columns)
		_column_width.push_back(Utils::get_polish_text_width(_font_table, column));
	_column_width[1] = Utils::get_polish_text_width(_font_table, "Czerwony"); // najszerszy napis
	_column_width[3] = Utils::get_polish_text_width(_font_table, "55:55:55");

	for (float width : _column_width) {
		_size.x += width + _margin_col;
	}
	_size.x -= _margin_col;
	_size.y = (_row_height + _margin_row) * (players_count + 1) - _margin_row;

	_left_top = c_MIDDLE - _size * .5f;
}

ScoreTable::~ScoreTable()
{
	delete[] _player_order;
}

void ScoreTable::sort_players() {
	std::sort(_player_order, _player_order + _players_count, [this](short ai, short bi) {
		const Player* a = _players[ai];
		const Player* b = _players[bi];

		if (a->Get_laps() != b->Get_laps()) {
			return a->Get_laps() > b->Get_laps();
		}

		return a->Get_current_checkpoint_index() > b->Get_current_checkpoint_index();
	});
}

void ScoreTable::Update() {
	sort_players();
}

void ScoreTable::Render() const {
	static const ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
	static const ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
	static const ALLEGRO_COLOR bg_color = al_map_rgba(49, 50, 50, 200);

	// t³o:
	static const float bg_margin = 40;
	al_draw_filled_rectangle(_left_top.x - bg_margin, _left_top.y - bg_margin, 
		_left_top.x + _size.x + bg_margin, _left_top.y + _size.y + bg_margin, bg_color);
	al_draw_rectangle(_left_top.x - bg_margin, _left_top.y - bg_margin,
		_left_top.x + _size.x + bg_margin, _left_top.y + _size.y + bg_margin, black, 15);

	// wiersz nag³ówkowy:
	float advance = 0;
	for (int i = 0; i < _columns.size(); i++) {
		Utils::draw_polish_text(_font_table, white, _left_top.x + advance + _margin_col * i, _left_top.y, 0, _columns[i]);
		advance += _column_width[i];
	}
	
	// zawartoœæ tabeli:
	for (int i = 0; i < _players_count; i++) {
		float y = _left_top.y + (_row_height + _margin_row) * (i + 1);
		short p_index = _player_order[i];

		Utils::draw_polish_text(_font_table, white, _left_top.x, y, 0, std::to_string(i + 1));
		advance = _column_width[0] + _margin_col;
		Utils::draw_polish_text(_font_table, c_PLAYER_COLOR[p_index], _left_top.x + advance, y, 0, c_PLAYER_NAME[p_index]);
		advance += _column_width[1] + _margin_col;
		Utils::draw_polish_text(_font_table, white, _left_top.x + advance, y, 0, std::to_string(_players[p_index]->Get_laps_to_display()));
		advance += _column_width[2] + _margin_col;
		if (i == 0) {
			Utils::draw_polish_text(_font_table, white, _left_top.x + advance, y, 0, _race_timer->Get_time_str());
		}
	}
}