#pragma once
#include "Scene.h"
#include "ResultsTable.h"

#include <allegro5/allegro_font.h>

class EndScene : public Scene
{
public:
	EndScene(GameCommands*, RaceStats*);
	~EndScene() override;
	void Update(KeyStatesTable) override;
	void Render() override;
private:
	ALLEGRO_FONT* _font_title;
	ALLEGRO_FONT* _font_menu;
	ResultsTable _results_table;
	RaceStats* _race_stats;

	float _title_height;
	float _menu_line_height;
	int _selected_option = 0;
	static constexpr int _option_count = 2;
	std::string _options[_option_count] = { "Zagraj ponownie", "Powrót do menu" };
};

