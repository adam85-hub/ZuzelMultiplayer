#pragma once
#include <memory>

#include "Scene.h"
#include "ResultsTable.h"
#include "Menu.h"

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
	ResultsTable _results_table;
	RaceStats* _race_stats;
	std::unique_ptr<Menu> _menu;

	float _title_height;
};

