#include "GameManager.h"

int GameManager::Run_game(Game* game) {
	init(game);
	run_main_loop();
	free_resources();

	return 0;
}