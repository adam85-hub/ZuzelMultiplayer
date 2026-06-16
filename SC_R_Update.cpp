#include "RaceScene.h"
#include "EndScene.h"
#include "Consts.h"

std::vector<double> join_serialised_states(const std::deque<std::vector<double>>& serialized_states) {
	std::vector<double> states;
	for (const auto& s : serialized_states) {
		states.insert(states.end(), s.begin(), s.end());
	}
	return states;
}

void RaceScene::Update(KeyStatesTable key_states) {
	// restart wyœcigu:
	if (key_states[ALLEGRO_KEY_R] & c_KEY_PRESSED) {
		std::cout << "RESTART!!\n";
		_game_commands->switch_scene.Execute(new RaceScene(_game_commands, _number_of_players, _number_of_ais, _number_of_laps));
		return;
	}

	if (_paused) {
		_pause_scene.Update(key_states);
		return;
	}
	
	if (key_states[ALLEGRO_KEY_P] & c_KEY_PRESSED or key_states[ALLEGRO_KEY_ESCAPE] & c_KEY_PRESSED) {
		pause();
	}
	
	_start_countdown.Update();
	if (!_start_countdown.Has_race_started())
		return;
	// po starcie wyścigu:

	short finished = 0;
	short ai_index = 0;
	for (int i = 0; i < _total_player_count; i++) {
		bool is_turning = key_states[_turn_buttons[i]] & c_KEY_DOWN;
		
		// decyzja agenta AI i kolejka stateów:
		if (_players[i]->Is_ai()) {
			_states[ai_index].push_back(static_cast<PlayerAI*>(_players[i])->Get_player_state()->serialise());
			if (_states[ai_index].size() > 8) {
				_states[ai_index].pop_front();
				is_turning = _decision_agent.act(join_serialised_states(_states[ai_index]));
			}
			else
				is_turning = 0;

			ai_index++;
		}

		_players[i]->Update(is_turning);

		if (_players[i]->Has_finished()) {
			finished++;
			continue;
		}
		if (_players[i]->Get_laps_to_display() > _number_of_laps)
			_players[i]->Finish(_race_timer.Get_time());
	}

	//--- COLLISION/CHECKPOINT ACTION---
	_collision_manager.Update();
	_score_table->Update();

	// koniec gry:
	if (finished == _total_player_count) {
		_game_commands->switch_scene.Execute(new EndScene(_game_commands, create_race_stats()));
		return;
	}
}
