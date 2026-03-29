#include "GameManager.h"
#include <allegro5/allegro_font.h>

#include "Consts.h"

void GameManager::run_main_loop() {
	ALLEGRO_EVENT event;
	bool redraw = true;

	unsigned char key_states[ALLEGRO_KEY_MAX];
	memset(key_states, 0, sizeof(key_states));

	al_start_timer(_timer);
	while (_game->Is_running()) {
		al_wait_for_event(_event_queue, &event); // wstrzymuje g³ówny bieg programu a¿ do pojawienia siê kolejnego zdarzenia
		
		switch (event.type) {
			case ALLEGRO_EVENT_TIMER:
				redraw = true; // pozwala na narysowanie nastêpnej klatki (dziêki temu klatki nie s¹ renderowane przy pojawieniu siê ka¿dego zdarzenia)
				_game->Update(key_states); // oblicza nowy stan gry
				
				for (int i = 0; i < ALLEGRO_KEY_MAX; i++) {
					key_states[i] |= c_KEY_PRESSED_HANDLED * (bool)(c_KEY_PRESSED & key_states[i]); // je¿eli key_pressed = true to key_pressed_handled = true
					key_states[i] &= ~(c_KEY_SEEN | c_KEY_PRESSED); // zeruje bity key_seen i key_pressed (1 i 3)
				}
				break;
			case ALLEGRO_EVENT_KEY_UP:
			case ALLEGRO_EVENT_KEY_DOWN:
				if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) { // only for debug
					_game->Exit();
					break;
				}

				update_key_states(key_states, event.type, event.keyboard.keycode);
				break;
			case ALLEGRO_EVENT_DISPLAY_CLOSE: 
				_game->Exit(); // koñczy wykonywanie pêtli w wypadku zamkniêcia g³ównego okna
				break;
			default:
				_game->Handle_event(event); // przekazuje zdarzenie do obs³u¿enia dalej
		}

		if (redraw && al_is_event_queue_empty(_event_queue)) { 
			render();
            redraw = false;
		}
	}
}