#pragma once
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <memory>

#include "SceneWithCommands.h"
#include "MenuModel.h"
#include "ResourceManager.h"

class MenuScene : public SceneWithCommands {
public:
	MenuScene(GameCommands* gameCommands);
	~MenuScene();
	void Render();
	void Update(KeyStatesTable);
private:
	std::unique_ptr<MenuModel> _menu_model;
	Utils::ResourceManager _resource_manager;

	ALLEGRO_FONT* _font_title;
	ALLEGRO_FONT* _font_menu_options;
	// Zmienne u¿ywane do renderowania (wyci¹gniête w celu optymalizacji):
#pragma region Render Variables
	int _title_height;
	std::vector<std::string> _menu_options;
	int _menu_option_height;
	ALLEGRO_COLOR _color_text_selected = al_map_rgb(219, 110, 53);
#pragma endregion
};
