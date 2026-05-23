#pragma once
#include "Scene.h"
#include "ResourceManager.h"
#include "allegro5/allegro_font.h"

class PauseScene : public Scene
{
public:
	PauseScene(GameCommands*);
	void Update(KeyStatesTable key_states) override;
	void Render() override;
private:
	Utils::ResourceManager _resource_manager;
	ALLEGRO_FONT* _font_title;
	ALLEGRO_COLOR _color_background = al_map_rgba(30, 30, 30, 200);
};

