#pragma once
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <vector>
#include <string>

#include "vec2.h"

class Table
{
public:
	Table(Utils::vec2 middle, std::vector<std::string> columns, int row_count, 
		ALLEGRO_COLOR font_color = al_map_rgb(255, 255, 255), float margin_col = 50, float margin_row = 10);
	virtual ~Table();
protected:
	void draw_title_row() const;
	void calculate_size();

	ALLEGRO_COLOR _font_color;
	ALLEGRO_FONT* _font_table;
	std::vector<std::string> _columns;

	std::vector<float> _column_width;
	Utils::vec2 _size;
	Utils::vec2 _left_top;
	const float _margin_col;
	const float _margin_row;
	float _row_height;
	int _row_count;
private:
	Utils::vec2 _middle;
};

