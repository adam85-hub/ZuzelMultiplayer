#include "RaceScene.h"
#include "CollisionDetector.h"
#include "draw_polish_text.h"

#include <allegro5/allegro_primitives.h>

void RaceScene::Render() {
	al_draw_scaled_bitmap(_race_track, 0, 0, al_get_bitmap_width(_race_track), al_get_bitmap_height(_race_track), 0, 0, c_RENDER_WIDTH, c_RENDER_HEIGHT, 0);

	for (int i = 0; i < _number_of_players; i++) {
		_players[i]->Render();
	}

	_score_table->Render();

	// drawing colliders (only dev):
	for (int i = 1; i < _inner_track_collider_len; i++) {
		al_draw_line(_inner_track_collider[i - 1].x, _inner_track_collider[i - 1].y,
			_inner_track_collider[i].x, _inner_track_collider[i].y, _color_text_default, 2);
	}

	al_draw_line(_inner_track_collider[0].x, _inner_track_collider[0].y, 
		_inner_track_collider[_inner_track_collider_len-1].x, _inner_track_collider[_inner_track_collider_len - 1].y, 
		_color_text_default, 2);

	for (int i = 1; i < _outer_track_collider_len; i++) {
		al_draw_line(_outer_track_collider[i - 1].x, _outer_track_collider[i - 1].y,
			_outer_track_collider[i].x, _outer_track_collider[i].y, _color_text_default, 2);
	}

	al_draw_line(_outer_track_collider[0].x, _outer_track_collider[0].y,
		_outer_track_collider[_outer_track_collider_len - 1].x, _outer_track_collider[_outer_track_collider_len - 1].y,
		_color_text_default, 2);

	// drawing start line (only dev):
	al_draw_line(_start_line[0].x, _start_line[0].y,
		_start_line[1].x, _start_line[1].y, al_map_rgb(255, 0, 0), 2);

	// drawing colliders (only dev):
	//_collision_manager.DrawColliders();
}