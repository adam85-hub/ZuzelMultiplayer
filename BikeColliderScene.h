#pragma once
#include "Scene.h"
#include "CreateColliderScene.h"
#include "round.h"

#include <filesystem>

// Ta scena s³u¿y tylko do stworzenia polygonu kolizji motoru
class BikeColliderScene : public Scene, CreateColliderScene {
public:
	BikeColliderScene(GameCommands* game_commads) : Scene(game_commads), CreateColliderScene() {
		ALLEGRO_BITMAP* bike_bitmap = al_load_bitmap("./Assets/bike_1.bmp");
		_bike_w = al_get_bitmap_width(bike_bitmap) * _scale;
		_bike_h = al_get_bitmap_height(bike_bitmap) * _scale;
		_bike_left = (c_RENDER_WIDTH - _bike_w) / 2.0;
		_bike_top = (c_RENDER_HEIGHT - _bike_h) / 2.0;

		_bike_bitmap = al_create_bitmap(_bike_w, _bike_h);
		_resource_manager.Track_resource(_bike_bitmap);

		al_set_target_bitmap(_bike_bitmap);
		al_draw_scaled_bitmap(bike_bitmap, 0, 0, al_get_bitmap_width(bike_bitmap), al_get_bitmap_height(bike_bitmap), 
			0, 0, _bike_w, _bike_h, 0);
		al_set_target_backbuffer(al_get_current_display());
	}

	void Update(KeyStatesTable key_states) {
		CreateColliderScene::Update(key_states);	

		if (key_states[ALLEGRO_KEY_ENTER] & c_KEY_PRESSED) {
			std::vector<Utils::vec2> relative_collider;
			relative_collider.reserve(_polygon_collider.size());

			// skalowanie polygonu aby by³ relatywny do nieprzeskalowanej bitmapy motoru
			for (int i = 0; i < _polygon_collider.size(); i++) {
				relative_collider.emplace_back(Utils::roundToNearestInt(std::max((_polygon_collider[i].x - _bike_left) / _scale, 0.0f)),
					relative_collider[i].y = Utils::roundToNearestInt(std::max((_polygon_collider[i].y - _bike_top) / _scale, 0.0f)));
			}

			save_to_file("bike_collider.txt", &relative_collider);
		}
	}

	void Render() {
		al_draw_bitmap(_bike_bitmap, _bike_left, _bike_top, 0);

		CreateColliderScene::Render();
	}
private:
	ALLEGRO_BITMAP* _bike_bitmap{};
	float _scale = 10;
	float _bike_h, _bike_w;
	float _bike_top, _bike_left;
};