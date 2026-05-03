#pragma once
#include "Consts.h"
#include "GameCommands.h"

// klasa bazowa scen
class Scene {
public:
	virtual void Update(KeyStatesTable key_states) = 0;
	virtual void Render() = 0;
	virtual ~Scene() {};
protected:
	Scene(GameCommands* game_commands) : _game_commands(game_commands) {}
	GameCommands* _game_commands;
	ALLEGRO_COLOR _color_text_default = al_map_rgb(255, 255, 255);
};