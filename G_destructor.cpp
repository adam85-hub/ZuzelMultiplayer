#include "Game.h"

Game::~Game() {
	delete _currentScene;
}