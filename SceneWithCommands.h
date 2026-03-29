#pragma once
#include "Scene.h"
#include "GameCommands.h"

class SceneWithCommands : public Scene {
protected:
	SceneWithCommands(GameCommands* game_commands) : _game_commands(game_commands) {}
	GameCommands* _game_commands;
};