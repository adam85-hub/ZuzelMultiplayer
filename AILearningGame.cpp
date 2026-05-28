#include "AILearningGame.h"
#include <allegro5/allegro5.h>

AILearningGame::~AILearningGame() {
	delete[] _key_states;
}

void AILearningGame::Init() {
	Game::Init();

	_race_scene = std::make_unique<RaceScene>(&_game_commands, 4, 3);

	_dqnAssets = DQNAManager::initAgent();

	_key_states = new unsigned char[ALLEGRO_KEY_MAX];
}

void AILearningGame::Update(KeyStatesTable _) {
	memset(_key_states, 0, ALLEGRO_KEY_MAX);
	// zmiana stanu klawiatury
	_race_scene->Update(_key_states);
}