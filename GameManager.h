#pragma once
#include <allegro5/allegro5.h>
#include <memory>

#include "Game.h"

// obiekty klasy GameManager odpowiadaj¹ za uruchomienie g³ównej pêtli programu
class GameManager {
public:
	int Run_game(); // uruchamia grê
private:
	void init(); // inicjalizuje allegro i zasoby potrzebne do uruchomienia pêtli g³ównej
	void run_main_loop(); // uruchamia pêtlê g³ówn¹
	void render(); // odpowiada za rysowanie nastêpnej klatki
	void free_resources(); // zwalnia zaalokowane zasoby todo: usun¹æ t¹ funkcjê(stwarza niebezpieczeñstwo podwójnego zwolnienia pamiêci)
private:
	void update_key_states(KeyStatesTable key_states, ALLEGRO_EVENT_TYPE event_type, int keycode);

	std::unique_ptr<Game> _game;
	ALLEGRO_TIMER* _timer = nullptr;
	ALLEGRO_EVENT_QUEUE* _event_queue = nullptr;
	ALLEGRO_DISPLAY* _display = nullptr;
};