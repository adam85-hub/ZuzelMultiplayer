#include "AILearningGame.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>

#include <format>
#include "draw_polish_text.h"
#include "Consts.h"
#include "DQN/NNFileManager.hpp"

static double calculateReward(const SpeedwayState& stateBefore, size_t action, const SpeedwayState& stateAfter) {
	double reward = 0.0;

	if (stateAfter.isHittingBoard) return -3000.0;
	if (stateAfter.isHittingPlayer)	reward -= 10.0;

	if (stateAfter.isPassingCheckpoint) { reward += 100.0; }

	double distanceImprovement = stateBefore.checkpointDistance - stateAfter.checkpointDistance;
	if(distanceImprovement > 0) reward += distanceImprovement * 4.0;

	reward -= 10; //existential penalty. time is passing, agent must be quick!!

	//double velocityDifference = stateAfter.velocity[0] - stateBefore.velocity[0] + stateAfter.velocity[1] - stateBefore.velocity[1];
	//reward -= velocityDifference * 1.0;
	
	//if (action == 1 && stateAfter.isHittingBoard == false && stateBefore.isHittingBoard == false) reward -= 4.0;

	return reward;
}

AILearningGame::~AILearningGame() {
	delete[] _key_states;
	al_destroy_font(_font);
}

void AILearningGame::Init() {
	Game::Init();
	_current_scene = new RaceScene(&_game_commands, 1, 3);

	_dqnAssets = DQNAManager::initAgent();
	_dqnAssets.update(NNFileManager::loadFNN("C:/Users/zimor/Documents/neural_network_2026-06-04_22-09-43"), false);
	
	_key_states = new unsigned char[ALLEGRO_KEY_MAX];
	_font = al_load_ttf_font(c_MAIN_FONT_PATH, c_RENDER_HEIGHT / 18, 0);

	_game_commands.switch_scene.Implement([this](Scene* scene) {
		delete _current_scene;

		_current_scene = dynamic_cast<RaceScene*>(scene);
	});
}

void AILearningGame::Update(KeyStatesTable _) {
	memset(_key_states, 0, ALLEGRO_KEY_MAX); // reset stanu klawiatury

	auto players = _current_scene->Get_players();
	auto player_count = _current_scene->Get_player_count();

	AI_players_act(players, player_count, 1); // skipujemy pierwszego gracza, on ma sie uczyc.

	auto learning_player = get_learning_player(players);

	handle_learning(learning_player, 4, 10000, 30000, true, 0);

	_update_iterator++;
	_total_updates++;
	_current_scene->Update(_key_states);
}

void AILearningGame::Render() const {
	
	//Utils::draw_polish_text(_font, al_map_rgb(255, 255, 255), c_RENDER_WIDTH / 2, c_RENDER_HEIGHT / 2, Utils::ALIGN_CENTER_XY, "Learning...");
	_current_scene->Render();
}

void AILearningGame::press_key(unsigned char key) {
	if (key >= ALLEGRO_KEY_MAX)
		throw std::out_of_range(std::format("Key must be between {} and {}", 0, ALLEGRO_KEY_MAX - 1));

	_key_states[key] = c_KEY_DOWN | c_KEY_PRESSED | c_KEY_SEEN;
}

void AILearningGame::AI_players_act(Player** players, size_t player_count, size_t skipped_players) {
	for (size_t i{ skipped_players }; i < player_count; i++) {
		PlayerAI* playerAi = dynamic_cast<PlayerAI*>(players[i]);
		if (!playerAi) {
			std::cerr << "Invalid player type!\n";
			_current_scene->Update(_key_states);
			return;
		}
		std::shared_ptr<SpeedwayState> state = playerAi->Get_player_state();
		size_t action = _dqnAssets.getAction(state);
		if (action) _key_states[_current_scene->Get_turn_buttons()[i]] |= c_KEY_DOWN;
	}
}

void AILearningGame::handle_learning(
	PlayerAI* learning_player, 
	size_t frame_skip,
	size_t nn_learning_frame_interval, 
	size_t nn_learning_epoch_frame_size,
	bool restart_on_board_hit,
	size_t learning_player_id
) {
	auto state = learning_player->Get_player_state();
	remember_transition(learning_player, state);

	size_t action;
	if (frame_skip == 0 || _update_iterator % frame_skip == 0)
		action = _dqnAssets.dqnAgent->act(*state);
	else
		action = _previous_action;

	_previous_action = action;
	_previous_state = state;

	//if (
	//	(_update_iterator > 0 && _update_iterator % nn_learning_frame_interval == 0)
	//	|| _current_scene->Get_paused()
	//	|| (restart_on_board_hit && state->isHittingBoard)
	//) {
	_dqnAssets.dqnAgent->replayLearn();

	if (
		_update_iterator == nn_learning_epoch_frame_size
		|| _current_scene->Get_paused()
		|| (restart_on_board_hit && state->isHittingBoard)
	) {
		_update_iterator = 0;
		_previous_state = nullptr;
		_epochs++;
		std::cout << "Epoch: " << _epochs << "\n";
			
		_key_states[ALLEGRO_KEY_R] |= c_KEY_PRESSED; // force restart
		
		
	}

	//}

	if (_total_updates > 0 && _total_updates % 5000 == 0) {
		_dqnAssets.dqnAgent->updateTargetNN();
	}

	 //zapis co 2000 epok
	if (_epochs > 0 && _epochs % 5000 == 0) 
		NNFileManager::saveFNN(*(_dqnAssets.dqnAgent->getTargetNN()), "C:/Users/zimor/Documents/");

	// zmiana stanu klawiatury
	if (action) _key_states[_current_scene->Get_turn_buttons()[learning_player_id]] |= c_KEY_DOWN;
}

void AILearningGame::remember_transition(PlayerAI* learning_player, std::shared_ptr<SpeedwayState> state) {
	if (_previous_state != 0) {
		bool finished = learning_player->Has_finished() || state->isHittingBoard;
		_dqnAssets.dqnAgent->remember(
			_previous_state->serialise(),
			_previous_action,
			calculateReward(*_previous_state, _previous_action, *state),
			state->serialise(),
			finished
		);
	}
}

PlayerAI* AILearningGame::get_learning_player(Player** players, size_t learning_player_id) {
	PlayerAI* learning_player = dynamic_cast<PlayerAI*>(players[learning_player_id]);
	if (!learning_player) {
		std::cerr << "Invalid learning player id!\n";
		_current_scene->Update(_key_states);
		return nullptr;
	}
	return learning_player;
}
