#include "NormalGame.h"
#include "MenuScene.h"

NormalGame::~NormalGame() {
	delete _current_scene;
}

void NormalGame::Init() {
	Game::Init();

	_current_scene = new MenuScene(&_game_commands);

	_game_commands.switch_scene.Implement([this](Scene* scene) {
		delete _current_scene;
		_current_scene = scene;
	});
}

void NormalGame::Update(KeyStatesTable key_states) {
	_current_scene->Update(key_states);
}

void NormalGame::Render() const {
	_current_scene->Render();
}