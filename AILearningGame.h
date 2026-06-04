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
	size_t _total_updates = 0;

	void AI_players_act(Player** players, size_t player_count, size_t skipped_players = 0);
	void handle_learning(
		PlayerAI* learning_player,
		size_t frame_skip,
		size_t nn_learning_frame_interval,
		size_t nn_learning_epoch_frame_size,
		bool restart_on_board_hit = false,
		size_t learning_player_id = 0
	);
	void remember_transition(PlayerAI* learning_player, std::shared_ptr<SpeedwayState> state);
	PlayerAI* get_learning_player(Player** players, size_t learning_player_id = 0);
};

