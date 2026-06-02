#include "Table.h"
#include <allegro5/allegro_ttf.h>
#include "Consts.h"
#include "draw_polish_text.h"

Table::Table(Utils::vec2 middle, std::vector<std::string> columns, int row_count, 
	ALLEGRO_COLOR font_color, float margin_col, float margin_row, float table_padding_x, float table_padding_y) :
	_columns(columns),
	_row_count(row_count),
	_margin_col(margin_col),
	_margin_row(margin_row),
	_table_padding_x(table_padding_x),
	_table_padding_y(table_padding_y),
	_font_color(font_color),
	_middle(middle)
{
	_font_table = al_load_ttf_font(c_MAIN_FONT_PATH, c_RENDER_HEIGHT / 20, 0);

	_row_height = al_get_font_line_height(_font_table);

	for (std::string column : _columns)
		_column_width.push_back(Utils::get_polish_text_width(_font_table, column));

	calculate_size();
}

Table::~Table() {
	al_destroy_font(_font_table);
}

void Table::draw_title_row() const {
	float advance = 0;
	for (int i = 0; i < _columns.size(); i++) {
		Utils::draw_polish_text(_font_table, _font_color, _left_top.x + advance + _margin_col * i, _left_top.y, 0, _columns[i]);
		advance += _column_width[i];
	}
}

void Table::calculate_size() {
	_size = Utils::vec2();

	for (float width : _column_width) {
		_size.x += width + _margin_col;
	}
	_size.x -= _margin_col;
	_size.y = (_row_height + _margin_row) * (_row_count + 1) - _margin_row;

	_left_top = _middle - _size * .5f;
}

Utils::vec2 Table::Get_size() const {
	return Utils::vec2(_size.x + 2 * _table_padding_x, _size.y + 2 * _table_padding_y);
}

Utils::vec2 Table::Get_top_left() const {
	return Utils::vec2(_left_top.x - _table_padding_x, _left_top.y - _table_padding_y);
}