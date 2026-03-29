#include "GameManager.h"

int GameManager::Run_game() {
	init();
	run_main_loop();
	free_resources();

	return 0;
}