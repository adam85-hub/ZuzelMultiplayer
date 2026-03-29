#pragma once
#include "PlayerModel.h"
#include "Consts.h"

// Zawiera logikê i stan odpowiedzialne za dzia³anie wyœcigu
class RaceModel {
public:
	RaceModel(short number_of_players) : _number_of_players(number_of_players) {
		_players = new PlayerModel*[_number_of_players];
		for (int i = 0; i < _number_of_players; i++) {
			_players[i] = new PlayerModel();
		}
	};

	~RaceModel() {
		for (int i = 0; i < _number_of_players; i++) {
			delete _players[i];
		}

		delete[] _players;
	}

private:
	short _number_of_players;
	PlayerModel** _players = nullptr;
public:
	const PlayerModel** players = _players;
};