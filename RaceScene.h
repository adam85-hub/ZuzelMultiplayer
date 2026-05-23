#pragma once
#include <memory>
#include <vector>

#include "Scene.h"
#include "ResourceManager.h"
#include "Player.h"
#include "CollisionManager.h"
#include "ScoreTable.h"
#include "PlayerAI.h"
#include "line.h"
#include "Countdown.h"
#include "PauseScene.h"

class RaceScene : public Scene {
public:
	RaceScene(GameCommands*, short number_of_players);
	~RaceScene();
	void Update(KeyStatesTable);
	void Render();

private:
	bool _only_ai_mode = false;
	bool _dev_mode = true;
  
	// usuwa poligony jeżeli nie są nullptr i wczytuje nowe z pliku
	void read_polygons_from_file();
	// tworzy nową tablicę i ustawia wartoœæ zmiennej out na jej adres 
	// (używać tylko jeżeli pamięć na którą wskazuje parametr out została zwolniona)
	void string_to_polygon(std::string str, Utils::vec2*& out, int& out_len);
	void add_barriers(const std::string &str, std::vector<Utils::line>& temp);
	void add_checkpoints(const std::string &str);

	Utils::ResourceManager _resource_manager;

	short _number_of_players;
	Player** _players;
	
	std::unique_ptr<ScoreTable> _score_table;
	Countdown _start_countdown;
	Timer _race_timer;
	unsigned int _turn_buttons[4];

	// --- COLLISION & CHECKPOINT ---
	CollisionManager _collision_manager;
	std::unique_ptr<Utils::line[]> _barriers;
	int _barriers_count = 0;

	PauseScene _pause_scene;

	std::unique_ptr<Utils::line[]> _checkpoints;
	int _checkpoints_count = 0;


	ALLEGRO_BITMAP* _race_track;
	Utils::vec2* _start_line = nullptr;

	bool _paused = false;
};