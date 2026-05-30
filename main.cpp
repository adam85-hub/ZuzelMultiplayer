#include "GameManager.h"
#include "LOG.h"
#include "NormalGame.h"
#include "AILearningGame.h"

int main() {
	GameManager gameManager;
	//NormalGame game;
	AILearningGame game;

	try {
		return gameManager.Run_game(&game);
	}
	catch (std::exception e) {
		LOG(e.what())
	}
}