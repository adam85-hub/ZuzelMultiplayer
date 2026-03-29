#include "GameManager.h"
#include "LOG.h"

int main() {
	GameManager gameManager;

	try {
		return gameManager.Run_game();
	}
	catch (std::exception e) {
		LOG(e.what())
	}
}