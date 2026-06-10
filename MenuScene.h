#pragma once
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <memory>

#include "ResourceManager.h"
#include "Scene.h"
#include "Menu.h"

class MenuScene : public Scene {
public:
	MenuScene(GameCommands* gameCommands);
	~MenuScene();
	void Render();
	void Update(KeyStatesTable);
private:
	Utils::ResourceManager _resource_manager;
	std::unique_ptr<Menu> _menu;

	const Utils::vec2 _left_top;

	ALLEGRO_FONT* _font_title;
	int _title_height;
};
