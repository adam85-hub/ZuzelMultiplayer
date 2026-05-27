#pragma once
#include "Scene.h"

#include <allegro5/allegro_font.h>

class EndScene : public Scene
{
public:
	EndScene(GameCommands*);
	~EndScene() override;
	void Update(KeyStatesTable) override;
	void Render() override;
private:
	ALLEGRO_FONT* _font_title;
};

