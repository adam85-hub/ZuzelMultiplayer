#include "GameCommands.h"
#include "MenuScene.h"
#include "Game.h"

#include "NewTrackScene.h"

void Game::Init() {
	_currentScene = new MenuScene(&_game_commands);
	//_currentScene = new NewTrackScene(&_game_commands); // only for development purposes
	
	_isRunning = true;

	_game_commands.exit.Implement([this](bool _) {
		Exit();
	});

	_game_commands.switch_scene.Implement([this](Scene* scene) {
		delete _currentScene;
		_currentScene = scene;
	});
}