#include "Game.h"

void Game::Init() {
	_is_running = true;

	_game_commands.exit.Implement([this](bool _) {
		Exit();
	});
}

void Game::Exit() {
	_is_running = false;
}

bool Game::Is_running() {
	return _is_running;
}