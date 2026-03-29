#include "Game.h"

void Game::Update(KeyStatesTable key_states) {
	_currentScene->Update(key_states);
}