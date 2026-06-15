#include "AILearningGame.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>

#include <format>
#include "draw_polish_text.h"
#include "Consts.h"
#include "DQN/NNFileManager.hpp"

constexpr size_t NN_SAVE_EPOCH_INTERVAL = 100;
constexpr size_t NN_EPOCH_FRAME_DURATION = 30000;

constexpr bool HEADLESS = false;
constexpr bool RESTART_ON_BOARD_HIT = false;
constexpr bool RESTART_ON_WRONG_DIRECTION = false;

constexpr bool LOAD_FNN = true;
constexpr bool RESET_EPSILON = true;
const std::string FNN_LOAD_PATH = "C:/Users/zimor/Documents/neural_network_2026-06-15_20-44-40";

static bool SUPERVISED_LEARNING = false;

// cosine of the vehicle-checkpoint angle, that when surpassed (|angle| > 135*), means that the vehicle is driving in the opposite way
constexpr double LIMIT_ANGLE = -0.707; 

static double calculateReward(const SpeedwayState& stateBefore, size_t action, SpeedwayState& stateAfter) {
	double reward = 0.0;

	// punishment for hitting the board. is smaller if the agent tried to turn
	//if (RESTART_ON_BOARD_HIT && stateAfter.isHittingBoard) return -500.0;
	if (stateAfter.isHittingBoard) {
		//if (action == 1) reward -= 100.0;
		//else reward -= 150.0;
		reward -= 100.0;
	}
	//if (stateAfter.relativeCheckpointAngle[1] < LIMIT_ANGLE) reward -= 150.0;

	//punishment for hitting a player
	if (stateAfter.isHittingPlayer)	reward -= 20.0;

	//reward for passing the checkpoint (only for the first time)
	if (stateAfter.isPassingCheckpoint && !stateBefore.isPassingCheckpoint) {
		reward += 150.0;
		//std::cout << "!!! CHECKPOINT ZALICZONY !!!\n";
	}
	else if (!stateBefore.isPassingCheckpoint) { //reward/punishment for driving towards/away from the checkpoint
		double distanceImprovement = stateBefore.checkpointDistance - stateAfter.checkpointDistance;
		reward += distanceImprovement * 20.0;
	}

	//punishment for not turning when side is close to the board
	//if ((stateAfter.distances[0] < 0.05 || stateAfter.distances[6] < 0.05) && action == 0) reward -= 5.0;

	//punishment for not turning when approaching board from the front
	//if ((stateAfter.distances[2] < 0.05 
	//		|| stateAfter.distances[3] < 0.05 
	//		|| stateAfter.distances[4] < 0.05)	
	//	&& action == 0) reward -= 5.0;

	//reward for being oriented towards the checkpoint
	//if (std::asin(stateAfter.checkpointAngle[0]) < 0.1) reward += 5.0;

	//punishment for turning on a straight
	//if (stateBefore.distances[3] + stateBefore.distances[4] + stateBefore.distances[2] > 2 && action == 1) reward -= 5.0;

	//existential penalty. time is passing, agent must be quick!!
	reward -= 0.1;

	//penalty for AFKing
	if (stateAfter.velocity[0] < 0.2 && stateAfter.velocity[1] < 0.2) reward -= 2.0;

	//penalty for slowing down
	//double speedBefore = std::hypot(stateBefore.velocity[0], stateBefore.velocity[1]);
	//double speedAfter = std::hypot(stateAfter.velocity[0], stateAfter.velocity[1]);
	//double speedDrop = speedBefore - speedAfter;
	//if (speedDrop > 0.0) reward -= speedDrop * 1.0;
	
	//penalty for turning when not hitting the board - stupid
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
	if(LOAD_FNN) _dqnAssets.update(NNFileManager::loadFNN(FNN_LOAD_PATH), RESET_EPSILON);
	
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

	//AI_players_act(players, player_count, 1); // skipujemy pierwszego gracza, on ma sie uczyc.

	auto learning_player = get_learning_player(players);
	if (SUPERVISED_LEARNING) _key_states[_current_scene->Get_turn_buttons()[0]] = _[_current_scene->Get_turn_buttons()[0]];
	handle_learning(learning_player, 2, NN_EPOCH_FRAME_DURATION, RESTART_ON_BOARD_HIT, RESTART_ON_WRONG_DIRECTION, 0);

	_update_iterator++;
	_total_updates++;
	if (SUPERVISED_LEARNING && !_key_states[ALLEGRO_KEY_R]) _current_scene->Update(_);
	else _current_scene->Update(_key_states);
}

void AILearningGame::Render() const {
	if (HEADLESS) Utils::draw_polish_text(_font, al_map_rgb(255, 255, 255), c_RENDER_WIDTH / 2, c_RENDER_HEIGHT / 2, Utils::ALIGN_CENTER_XY, "Learning...");
	else _current_scene->Render();
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
		std::shared_ptr<SpeedwayState> state = playerAi->_player_state;
		size_t action = _dqnAssets.getAction(state);
		if (action) _key_states[_current_scene->Get_turn_buttons()[i]] |= c_KEY_DOWN;
	}
}

void AILearningGame::handle_learning(
	PlayerAI* learning_player, 
	size_t frame_skip,
	//size_t nn_learning_frame_interval, 
	size_t nn_learning_epoch_frame_size,
	bool restart_on_board_hit,
	bool restart_on_wrong_direction,
	size_t learning_player_id
) {
	auto state = learning_player->Get_player_state();
	
	//if (state == nullptr) std::cout << "STATE = NULLPTR!\n";
	//else if (state->isHittingBoard) std::cout << "STATE IS HITTING BOARD!!\n";

	if (state != nullptr) save_state(state);

	bool is_decision_frame = frame_skip == 0 || _update_iterator % frame_skip == 0;

	if (SUPERVISED_LEARNING) {
		if (is_decision_frame) {
			size_t human_action = (_key_states[_current_scene->Get_turn_buttons()[0]] & c_KEY_DOWN) ? 1 : 0;
			_demonstrative_transitions.push_back({ get_serialised_states(), human_action });
		}
		if (_epochs == 3) {
			_dqnAssets.dqnAgent->supervisedLearning(_demonstrative_transitions);

			_epochs = 0;
			SUPERVISED_LEARNING = false;
			_demonstrative_transitions.clear();
			_dqnAssets.clearEpsilon();

			_key_states[ALLEGRO_KEY_R] |= c_KEY_PRESSED; // force restart
			return;
		}
		if (state != nullptr && _current_scene->Get_paused()) {
			_epochs++;
			_key_states[ALLEGRO_KEY_R] |= c_KEY_PRESSED; // force restart
		}
		return;
	}

	if(state != nullptr && _previous_state != nullptr) _cumulative_reward += calculateReward(*_previous_state, _previous_action, *state);
	
	size_t action;

	bool is_board_hit = state != nullptr && restart_on_board_hit && state->isHittingBoard;
	bool is_wrong_direction = state != nullptr && restart_on_wrong_direction && state->relativeCheckpointAngle[1] < LIMIT_ANGLE;
	bool is_terminal_hit = is_board_hit || is_wrong_direction;

	if (is_decision_frame || is_terminal_hit) {
		if(_previous_state != nullptr) remember_transition(learning_player, state, _cumulative_reward, restart_on_board_hit, restart_on_wrong_direction);
		if (!is_terminal_hit) {
			action = _dqnAssets.dqnAgent->act(get_serialised_states());
		}
		else {
			action = _previous_action; // w terminalnym stanie nie ma sensu pytać sieci o zdanie
		}
		_previous_serialised_states = get_serialised_states();
		_previous_action = action;
		_cumulative_reward = 0;

		_dqnAssets.dqnAgent->replayLearn();
	} else action = _previous_action;
	
	_previous_state = state;

	//if (
	//	(_update_iterator > 0 && _update_iterator % nn_learning_frame_interval == 0)
	//	|| _current_scene->Get_paused()
	//	|| (restart_on_board_hit && state->isHittingBoard)
	//) {
	
	if (
		state != nullptr && 
		(_update_iterator == nn_learning_epoch_frame_size
			|| _current_scene->Get_paused()
			|| is_terminal_hit
		)
	) {
		_update_iterator = 0;
		_previous_state = nullptr;
		_epochs++;
		std::cout << "Epoch: " << _epochs << "\n";
		_serialised_states.clear();
			
		_key_states[ALLEGRO_KEY_R] |= c_KEY_PRESSED; // force restart
		
		if (_epochs > 0 && _epochs % NN_SAVE_EPOCH_INTERVAL == 0) {
			_dqnAssets.dqnAgent->updateTargetNN();
			NNFileManager::saveFNN(*(_dqnAssets.dqnAgent->getTargetNN()), "C:/Users/zimor/Documents/");
			std::cout << "SAVED FNN!\n";
		}
	}

	//}

	if (_total_updates > 0 && _total_updates % 30000 == 0) {
		_dqnAssets.dqnAgent->updateTargetNN();
	}

	// zmiana stanu klawiatury
	if (action) _key_states[_current_scene->Get_turn_buttons()[learning_player_id]] |= c_KEY_DOWN;
}

void AILearningGame::remember_transition(
	PlayerAI* learning_player, 
	std::shared_ptr<SpeedwayState> currentState, 
	double reward, 
	bool restart_on_board_hit,
	bool restart_on_wrong_direction
) {
	bool finished = learning_player->Has_finished() 
		|| (currentState->isHittingBoard && restart_on_board_hit) 
		|| (currentState->relativeCheckpointAngle[1] < LIMIT_ANGLE && restart_on_wrong_direction);
	_dqnAssets.dqnAgent->remember(
		_previous_serialised_states,
		_previous_action,
		reward,
		get_serialised_states(),
		finished
	);
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

std::vector<double> AILearningGame::get_serialised_states() {
	std::vector<double> states;
	for (const auto& s : _serialised_states) {
		states.insert(states.end(), s.begin(), s.end());
	}
	return states;
}

void AILearningGame::save_state(std::shared_ptr<SpeedwayState> state) {
	auto stateVec = state->serialise();
	if (_serialised_states.empty()) {
		for (int i = 0; i < STATES_TO_PROCESS; i++)
			_serialised_states.push_back(stateVec);
		return;
	}
	if (_serialised_states.size() >= STATES_TO_PROCESS) _serialised_states.pop_front();
	_serialised_states.push_back(stateVec);
}
