#include <allegro5/allegro_ttf.h>
#include <filesystem>

#include "RaceScene.h"
#include "vec2.h"
#include "LOG.h"
#include "check_functions.h"

RaceScene::RaceScene(GameCommands* gameCommands, short number_of_players) : 
	Scene(gameCommands), 
	_number_of_players(number_of_players),
	_turn_buttons{ALLEGRO_KEY_LCTRL, ALLEGRO_KEY_SPACE, ALLEGRO_KEY_RCTRL, ALLEGRO_KEY_DOWN}
{
	_font_score_table = al_load_ttf_font(c_MAIN_FONT_PATH, c_RENDER_HEIGHT / 10, 0);
	_resource_manager.Track_resource(_font_score_table);

	// inicjalizacja wszystkich polygonów
	read_polygons_from_file();

	// inicjalizacja i ustawienie graczy na starcie:
	_players = new Player * [_number_of_players];
	std::filesystem::path path_to_bitmap;
	ALLEGRO_BITMAP* bike_bitmap;
	Utils::vec2 initial_position(_start_line[0].x, _start_line[0].y);
	const float start_h = _start_line[1].y - _start_line[0].y;
	for (int i = 0; i < _number_of_players; i++) {
		path_to_bitmap = "./Assets/bike_" + std::to_string(i+1) + ".bmp";
		bike_bitmap = al_load_bitmap(path_to_bitmap.string().c_str());
		Utils::check_resource_loaded(bike_bitmap, path_to_bitmap.string());

		_players[i] = new Player(initial_position, bike_bitmap);
		_players[i]->position.y += start_h / _number_of_players * i + start_h / (2*_number_of_players);
		_players[i]->position.x -= _players[i]->bike_width / 2;
		al_destroy_bitmap(bike_bitmap);

		//--- set colliders for players ---
		_collision_manager.AddCollider(new Collider(ColliderType::Player,_players[i], 11)); ///tutaj sie ustala promien hitboxa
	}
	
	///============================================COLLIDERES============================================================
	//--- set colliders for inner track ---
	for (int i = 0; i < _inner_track_collider_len - 1; ++i) {
		Collider* wall = new Collider(ColliderType::Wall, nullptr,0.05);
		wall->SetStartPoint(_inner_track_collider[i]);
		wall->SetEndPoint(_inner_track_collider[i + 1]);
		_collision_manager.AddCollider(wall);
	}
	
	Collider* wall = new Collider(ColliderType::Wall, nullptr, 0.05);
	wall->SetStartPoint(_inner_track_collider[_inner_track_collider_len - 1]);
	wall->SetEndPoint(_inner_track_collider[0]);
	_collision_manager.AddCollider(wall);

	//--- set colliders for outer track ---
	for (int i = 0; i < _outer_track_collider_len - 1; ++i) {
		Collider* wall = new Collider(ColliderType::Wall, nullptr, 0.05);
		wall->SetStartPoint(_outer_track_collider[i]);
		wall->SetEndPoint(_outer_track_collider[i + 1]);
		_collision_manager.AddCollider(wall);
	}

	wall = new Collider(ColliderType::Wall, nullptr, 0.05);
	wall->SetStartPoint(_outer_track_collider[_outer_track_collider_len - 1]);
	wall->SetEndPoint(_outer_track_collider[0]);
	_collision_manager.AddCollider(wall);

	// za³adowanie bitmapy trasy:
	constexpr const char* track_path = "./Assets/track.png";
	_race_track = al_load_bitmap(track_path);
	Utils::check_resource_loaded(_race_track, track_path);
	_resource_manager.Track_resource(_race_track);
}