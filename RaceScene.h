#pragma once
#include "SceneWithCommands.h"
#include "ResourceManager.h"
#include "Player.h"

class RaceScene : public SceneWithCommands {
public:
	RaceScene(GameCommands*, short number_of_players);
	~RaceScene();
	void Update(KeyStatesTable);
	void Render();
private:
	// usuwa poligony je¿eli nie s¹ nullptr i wczytuje nowe z pliku
	void read_polygons_from_file();
	// tworzy now¹ tablicê i ustawia wartoœæ zmiennej out na jej adres 
	// (u¿ywaæ tylko je¿eli pamiêæ na któr¹ wskazuje parametr out zosta³a zwolniona)
	void string_to_polygon(std::string str, Utils::vec2*& out, int& out_len);

	Utils::ResourceManager _resourceManager;

	short _number_of_players;
	Player** _players;

	ALLEGRO_BITMAP* _race_track;
	Utils::vec2* _inner_track_collider = nullptr;
	int _inner_track_collider_len = 0;
	Utils::vec2* _outer_track_collider = nullptr;
	int _outer_track_collider_len = 0;
	Utils::vec2* _start_line = nullptr;
	Utils::vec2* _bike_collider = nullptr;
	int _bike_collider_len = 0;

	ALLEGRO_FONT* _font_score_table;
};