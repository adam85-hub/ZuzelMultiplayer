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

	std::unique_ptr<RaceScene> _race_scene;
	DQNAssets _dqnAssets;
	KeyStatesTable _key_states = nullptr;
	ALLEGRO_FONT* _font;
};

