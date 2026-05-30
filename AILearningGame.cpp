#include "AILearningGame.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>

#include <format>
#include "draw_polish_text.h"
#include "Consts.h"
#include "DQN/NNFileManager.hpp"

static double calculateReward(const SpeedwayState& stateBefore, size_t action, const SpeedwayState& stateAfter) {
	double reward = 0.0;

	if (stateAfter.isHittingBoard) reward -= 25.0;
	if (stateAfter.isHittingPlayer)	reward -= 4.0;

	if (stateAfter.isPassingCheckpoint) reward += 80.0;

	double distanceImprovement = stateBefore.checkpointDistance - stateAfter.checkpointDistance;
	reward += distanceImprovement * 15.0;

	reward -= 0.3; //existential penalty. time is passing, agent must be quick!!

	double velocityDifference = stateAfter.velocity[0] - stateBefore.velocity[0] + stateAfter.velocity[1] - stateBefore.velocity[1];
	reward -= velocityDifference * 1.0;
	//if (action == 1 && stateAfter.isHittingBoard == false) reward -= 2.0;

	return reward;
}

AILearningGame::~AILearningGame() {
	delete[] _key_states;
	al_destroy_font(_font);
}

void AILearningGame::Init() {
	Game::Init();

	_current_scene = new RaceScene(&_game_commands, 2, 3);

	_dqnAssets = DQNAManager::initAgent();

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
	auto playerCount = _current_scene->Get_player_count();

	for (size_t i{1}; i < playerCount; i++) {
		PlayerAI* playerAi = dynamic_cast<PlayerAI*>(players[i]);
		if (!playerAi) {
			std::cerr << "Invalid player type!\n";
			_current_scene->Update(_key_states);
			return;
		}
		std::shared_ptr<SpeedwayState> state = playerAi->Get_player_state();
		size_t action = _dqnAssets.getAction(state);
		if(action) _key_states[_current_scene->Get_turn_buttons()[i]] |= c_KEY_DOWN;
	}

	PlayerAI* learningPlayer = dynamic_cast<PlayerAI*>(players[0]);
	if (!learningPlayer) {
		std::cerr << "Invalid player type!\n";
		_current_scene->Update(_key_states);
		return;
	}
	std::shared_ptr<SpeedwayState> state = learningPlayer->Get_player_state();
	
	size_t action = _dqnAssets.dqnAgent->act(*state);

	if (_previous_state != 0) {
		_dqnAssets.dqnAgent->remember(
			_previous_state->serialise(),
			_previous_action,
			calculateReward(*_previous_state, _previous_action, *state),
			state->serialise(), learningPlayer->Has_finished()
		);
	}

	_previous_state = state;
	_previous_action = action;

	_update_iterator++;
	
	// zmiana stanu klawiatury
	if (action) _key_states[_current_scene->Get_turn_buttons()[0]] |= c_KEY_DOWN;

	

	if ((_update_iterator > 0 && _update_iterator % 20000 == 0) || _current_scene->Get_paused()) {
		std::cout << _update_iterator << "\n";
		_dqnAssets.dqnAgent->replayLearn();

		if (_update_iterator == 20000 || _current_scene->Get_paused()) {
			_update_iterator = 0;
			_previous_state = 0;
			_dqnAssets.dqnAgent->updateTargetNN();
			_epochs++;
			if (_epochs % 10 == 0) {
				NNFileManager::saveFNN(*(_dqnAssets.target), "C:/Users/zimor/Documents/");
			}
		}
		//auto game_commands = _race_scene->Get_game_commands();
		//_race_scene->_game_commands->switch_scene.Execute(new RaceScene(_race_scene->_game_commands, playerCount, _race_scene->Get_lap_count()));
		_key_states[ALLEGRO_KEY_R] |= c_KEY_PRESSED;
	}
	
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