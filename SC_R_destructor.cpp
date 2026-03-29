#include "RaceScene.h"

RaceScene::~RaceScene() {
	for (int i = 0; i < _number_of_players; i++) {
		delete _players[i];
	}

	delete[] _players;
	delete[] _inner_track_collider;
	delete[] _outer_track_collider;
}