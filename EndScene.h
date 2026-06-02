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
	ResultsTable _results_table;
	RaceStats* _race_stats;

	float _title_height;
};

