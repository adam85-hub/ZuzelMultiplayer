#include "ResultsTable.h"
#include "Consts.h"
#include "draw_polish_text.h"
#include "Timer.h"

#include <allegro5/allegro_primitives.h>

ResultsTable::ResultsTable(RaceStats* race_stats) :
	Table(c_MIDDLE, {"Miejsce", "Gracz", "Czas"}, race_stats->player_count),
	_race_stats(race_stats)
{
	_column_width[1] = Utils::get_polish_text_width(_font_table, "Czerwony");
	_column_width[2] = Utils::get_polish_text_width(_font_table, "22:22:22");

	calculate_size();
}

void ResultsTable::Render() const {
	static const ALLEGRO_COLOR bg_color = al_map_rgb(49, 50, 50);

	// t³o:
	al_draw_filled_rectangle(_left_top.x - _table_padding_x, _left_top.y - _table_padding_y,
		_left_top.x + _size.x + _table_padding_x, _left_top.y + _size.y + _table_padding_y, bg_color);

	draw_title_row();

	float left = 0, top = 0;
	int p_index;
	for (int i = 0; i < _race_stats->player_count; i++) {
		top = _left_top.y + (i+1) * (_row_height + _margin_row);
		left = _left_top.x;
		p_index = _race_stats->player_order[i];

		Utils::draw_polish_text(_font_table, _font_color, left, top, 0, std::to_string(i + 1));
		left += _column_width[0] + _margin_col;

		Utils::draw_polish_text(_font_table, c_PLAYER_COLOR[p_index], left, top, 0, c_PLAYER_NAME[p_index]);
		left += _column_width[1] + _margin_col;

		Utils::draw_polish_text(_font_table, _font_color, left, top, 0, Timer::Time_to_str(_race_stats->times[p_index]));
	}
}
