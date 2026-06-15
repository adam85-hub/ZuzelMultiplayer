#pragma once
#include <vector>
#include <string>

#include <allegro5/allegro_font.h>
#include "Consts.h"
#include "Option.h"

class Menu {
public:
	Menu(Utils::vec2 top_left, bool centered = true, int font_size = c_RENDER_HEIGHT / 20, int line_margin = 10);
	~Menu();

	void Update(KeyStatesTable);
	void Render() const;

	void Add_option(Option*);
	int Get_option_value(int index);
private:
	ALLEGRO_FONT* _font;
	Utils::vec2 _top_left;
	float _line_height;
	const float _line_margin;
	const bool _centered;

	std::vector<Option*> _options;
	int _selected_option = 0;
};