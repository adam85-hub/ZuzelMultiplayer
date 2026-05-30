#pragma once
#include "memory"
#include "Game.h"
#include "RaceScene.h"
#include "DQNAManager.h"

class AILearningGame : public Game
{
public:
	~AILearningGame() override;
	void Init() override;
	void Update(KeyStatesTable) override;
	void Render() const override;
private:
	void press_key(unsigned char key);
	RaceScene* _current_scene = nullptr;

	DQNAssets _dqnAssets;
	KeyStatesTable _key_states = nullptr;
	ALLEGRO_FONT* _font;

	size_t _epochs = 0;
	std::shared_ptr<SpeedwayState> _previous_state = 0;
	size_t _previous_action;
	size_t _update_iterator = 0;
};

