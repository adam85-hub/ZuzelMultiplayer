#include "GameCommands.h"
#include "MenuScene.h"
#include "Game.h"

//#include "CreateCheckpointsScene.h"

void Game::Init() {
	_currentScene = new MenuScene(&_game_commands);
	//_currentScene = new CreateCheckpointsScene(&_game_commands); // only for development purposes
	
	_isRunning = true;

	_game_commands.exit.Implement([this](bool _) {
		Exit();
	});

	_game_commands.switch_scene.Implement([this](Scene* scene) {
		delete _currentScene;
		_currentScene = scene;
	});

	// tworzenie agenta DQN
	dqnAssets = DQNAManager::initAgent();
}