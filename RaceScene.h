#pragma once
#include <memory>
#include <vector>
#include <iostream>

#include "Scene.h"
#include "ResourceManager.h"
#include "Player.h"
#include "CollisionManager.h"
#include "ScoreTable.h"
#include "PlayerAI.h"
#include "line.h"
#include "Countdown.h"
#include "PauseScene.h"
#include "RaceStats.h"

class RaceScene : public Scene {
public:
	RaceScene(GameCommands*, short number_of_players, short number_of_laps);
	~RaceScene();
	void Update(KeyStatesTable);
	void Render();

	short Get_player_count() const { return _number_of_players; }
	Player** Get_players() const { return _players; }
	GameCommands* Get_game_commands() const { return _game_commands; }
	short Get_lap_count() const { return _number_of_laps; }
	unsigned int* Get_turn_buttons() { return _turn_buttons; }
	bool Get_paused() const { return _paused; }
private:
	bool _only_ai_mode = true;
	bool _dev_mode = false;
  
	// usuwa poligony jeżeli nie są nullptr i wczytuje nowe z pliku
	void read_polygons_from_file();
	// tworzy nową tablicę i ustawia wartoœæ zmiennej out na jej adres 
	// (używać tylko jeżeli pamięć na którą wskazuje parametr out została zwolniona)
	void string_to_polygon(std::string str, Utils::vec2*& out, int& out_len);
	void add_barriers(const std::string &str, std::vector<Utils::line>& temp);
	void add_checkpoints(const std::string &str);
	void pause();
	void unpause();
	RaceStats* create_race_stats() const;

	Utils::ResourceManager _resource_manager;

	const short _number_of_laps;
	const short _number_of_players;
	Player** _players;
	
	std::unique_ptr<ScoreTable> _score_table;
	Countdown _start_countdown;
	Timer _race_timer;
	unsigned int _turn_buttons[4];

	// --- COLLISION & CHECKPOINT ---
	CollisionManager _collision_manager;

	std::unique_ptr<Utils::line[]> _barriers;
	int _barriers_count = 0;

	std::unique_ptr<Utils::line[]> _checkpoints;
	int _checkpoints_count = 0;
	ALLEGRO_BITMAP* _race_track;
	Utils::vec2* _start_line = nullptr;

	// Pauza:
	Utils::Command<bool> _unpause_cmd;
	PauseScene _pause_scene;
	bool _paused = false;
};