#include "GameManager.h"

void GameManager::update_key_states(KeyStatesTable key_states, ALLEGRO_EVENT_TYPE event_type, int keycode) {
	// w tablicy key_states:
	// 1 w pierwszym bicie(key_seen) oznacza ¿e przyciœniêcie klawisza wyst¹pi³o pomiêdzy uruchomieniami logiki gry
	// 1 w drugim bicie(key_down) oznacza ¿e klawisz jest naciœniêty
	// 3ci(key_pressed) i 4ty(key_pressed_handled) bit pozwalaj¹ na wywo³anie odpowiedniego zdarzenia tylko raz na przyciœniêcie klawisza
	if (event_type == ALLEGRO_EVENT_KEY_DOWN) {
		key_states[keycode] = c_KEY_SEEN | c_KEY_DOWN; // Ustawia 1 na dwóch pierwszych bitach
		key_states[keycode] |= c_KEY_PRESSED * (~(bool)(key_states[keycode] & c_KEY_PRESSED_HANDLED));
		// ustawia bit key_pressed na 1 je¿eli bit key_pressed_handled ma wartoœæ 0
	}
	else if (event_type == ALLEGRO_EVENT_KEY_UP) {
		key_states[keycode] &= ~(c_KEY_DOWN | c_KEY_PRESSED_HANDLED); // zeruje drugi i czwarty bit
	}
}