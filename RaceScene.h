#pragma once
#include "Scene.h"
#include "ResourceManager.h"
#include "Player.h"
#include "CollisionManager.h"

class RaceScene : public Scene {
public:
	RaceScene(GameCommands*, short number_of_players);
	~RaceScene();
	void Update(KeyStatesTable);
	void Render();

private:
	// usuwa poligony jeżeli nie są nullptr i wczytuje nowe z pliku
	void read_polygons_from_file();
	// tworzy nową tablicę i ustawia wartoœæ zmiennej out na jej adres 
	// (używać tylko jeżeli pamięć na którą wskazuje parametr out została zwolniona)
	void string_to_polygon(std::string str, Utils::vec2*& out, int& out_len);

	Utils::ResourceManager _resource_manager;

	short _number_of_players;
	Player** _players;
	CollisionManager _collision_manager;
	unsigned int _turn_buttons[4];

	ALLEGRO_BITMAP* _race_track;
	Utils::vec2* _inner_track_collider = nullptr;
	int _inner_track_collider_len = 0;
	Utils::vec2* _outer_track_collider = nullptr;
	int _outer_track_collider_len = 0;
	Utils::vec2* _start_line = nullptr;

	bool _paused = false;

	ALLEGRO_FONT* _font_score_table;
};