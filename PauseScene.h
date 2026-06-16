#pragma once
#include <memory>
#include "Scene.h"
#include "Menu.h"
#include "ResourceManager.h"
#include "allegro5/allegro_font.h"

class PauseScene : public Scene
{
public:
	PauseScene(GameCommands*, Utils::Command<bool>*, int, int, int);
	~PauseScene();
	void Update(KeyStatesTable key_states) override;
	void Render() override;
private:
	Utils::Command<bool>* _unpause_cmd;
	std::unique_ptr<Menu> _menu;

	const float _title_top = c_RENDER_HEIGHT / 3;
	Utils::ResourceManager _resource_manager;
	ALLEGRO_FONT* _font_title;
	ALLEGRO_COLOR _color_background = al_map_rgba(30, 30, 30, 225);
};	

