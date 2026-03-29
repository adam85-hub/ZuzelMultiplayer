#pragma once
#include "SceneWithCommands.h"
#include "vec2.h"
#include "ResourceManager.h"
#include "CreateColliderScene.h"

// Ta scena s³u¿y tylko do stworzenia i zapisania poligonów s³u¿¹cych do obs³ugi kolizji
// (czyli tak naprawdê zaznaczenia krawêdzi toru)
class NewTrackScene : public SceneWithCommands, CreateColliderScene {
public:
	NewTrackScene(GameCommands* gameCommands) : SceneWithCommands(gameCommands), CreateColliderScene() {
		ALLEGRO_BITMAP* race_track = al_load_bitmap("./Assets/track.png");
		_race_track = al_create_bitmap(c_RENDER_WIDTH, c_RENDER_HEIGHT);
		_resource_manager.Track_resource(_race_track);
		al_set_target_bitmap(_race_track);
		al_draw_scaled_bitmap(race_track, 0, 0, al_get_bitmap_width(race_track), al_get_bitmap_height(race_track), 0, 0, c_RENDER_WIDTH, c_RENDER_HEIGHT, 0);
		al_set_target_backbuffer(al_get_current_display());
	}

	void Render() {
		al_draw_bitmap(_race_track, 0, 0, 0);

		CreateColliderScene::Render();
	}

	void Update(KeyStatesTable key_states) {
		CreateColliderScene::Update(key_states);

		if (key_states[ALLEGRO_KEY_ENTER] & c_KEY_PRESSED) {
			save_to_file("start_line.txt");
		}
	}
private:
	ALLEGRO_BITMAP* _race_track;
};