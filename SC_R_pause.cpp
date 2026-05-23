#include "RaceScene.h"

void RaceScene::pause() {
	_paused = true;
	if (!_start_countdown.Has_ended())
		_start_countdown.Pause();
	_race_timer.Pause(); 
}

void RaceScene::unpause() {
	_paused = false;
	if (!_start_countdown.Has_ended())
		_start_countdown.Unpause();
	_race_timer.Unpause();
}