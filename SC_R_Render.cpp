#include "RaceScene.h"
#include "draw_polish_text.h"

#include <allegro5/allegro_primitives.h>

void RaceScene::Render() {
	al_draw_scaled_bitmap(_race_track, 0, 0, al_get_bitmap_width(_race_track), al_get_bitmap_height(_race_track), 0, 0, c_RENDER_WIDTH, c_RENDER_HEIGHT, 0);

	for (int i = 0; i < _total_player_count; i++) {
		_players[i]->Render();
	}

#pragma region Only dev
	// drawing start line (only dev):
	//al_draw_line(_start_line[0].x, _start_line[0].y,
	//	_start_line[1].x, _start_line[1].y, al_map_rgb(255, 0, 0), 2);

	// drawing colliders (only dev):
	if (_dev_mode)_collision_manager.Draw_colliders();
#pragma endregion

	if (_start_countdown.Has_ended() == false) {
		_start_countdown.Render();
		if (_paused)
			_pause_scene.Render();
		return;
	}

	// po starcie wyœcigu:
	_score_table->Render();

	if (_paused)
		_pause_scene.Render();
}