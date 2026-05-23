#include <filesystem>

#include "RaceScene.h"
#include "vec2.h"
#include "LOG.h"
#include "check_functions.h"

RaceScene::RaceScene(GameCommands* gameCommands, short number_of_players) : 
	Scene(gameCommands), 
	_pause_scene(gameCommands),
	_number_of_players(number_of_players),
	_turn_buttons{ALLEGRO_KEY_LCTRL, ALLEGRO_KEY_SPACE, ALLEGRO_KEY_RCTRL, ALLEGRO_KEY_DOWN},
	_start_countdown(3)
{
	// inicjalizacja wszystkich polygonów
	read_polygons_from_file();

	// inicjalizacja i ustawienie graczy na starcie:
	_players = new Player * [_number_of_players];
	std::filesystem::path path_to_bitmap;
	ALLEGRO_BITMAP* bike_bitmap;
	Utils::vec2 initial_position(_start_line[0].x, _start_line[0].y);
	const float start_h = _start_line[1].y - _start_line[0].y;

	//COLORY GRACZY
	ALLEGRO_COLOR player_colors[] = {
	al_map_rgb(255, 0, 0),   // Czerwony
	al_map_rgb(0, 255, 0),   // Zielony
	al_map_rgb(0, 0, 255),   // Niebieski
	al_map_rgb(255, 255, 0)  // Żółty
	};


	for (int i = 0; i < _number_of_players; i++) {
		path_to_bitmap = "./Assets/bike_" + std::to_string(i+1) + ".bmp";
		bike_bitmap = al_load_bitmap(path_to_bitmap.string().c_str());
		Utils::check_resource_loaded(bike_bitmap, path_to_bitmap.string());

		if(_only_ai_mode)
			_players[i] = new PlayerAI(initial_position, bike_bitmap);
		else
			_players[i] = new Player(initial_position, bike_bitmap);
		
		_players[i]->position.y += start_h / _number_of_players * i + start_h / (2*_number_of_players);
		_players[i]->position.x -= _players[i]->bike_width / 2;
		_players[i]->Set_color(player_colors[i % 4]);
		al_destroy_bitmap(bike_bitmap);

		//--- set colliders for players --- 
		_collision_manager.Add_player(_players[i]);
	}

	_score_table = std::make_unique<ScoreTable>(_players, number_of_players, &_race_timer);
	
	//--- dodanie barier ---
	_collision_manager.Add_walls(_barriers.get(), _barriers_count);

	// --- AI LASERS---
	if (_only_ai_mode)PlayerAI::Add_walls(_barriers.get(), _barriers_count);

	//--- dodanie checkpointów ---
	_collision_manager.Add_checkpoints(_checkpoints.get(), _checkpoints_count);
	Player::checkpoint_count = _checkpoints_count;

	// załadowanie bitmapy trasy:
	constexpr const char* track_path = "./Assets/track.png";
	_race_track = al_load_bitmap(track_path);
	Utils::check_resource_loaded(_race_track, track_path);
	_resource_manager.Track_resource(_race_track);

	_start_countdown.Start();
	_start_countdown.Execute_on_start([this]() -> void {_race_timer.Start(); });
}