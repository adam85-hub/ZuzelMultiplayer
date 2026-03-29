#include <stdexcept>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "GameManager.h"
#include "check_functions.h"
#include "Consts.h"

void GameManager::init() {
	Utils::check_initialized(al_init(), "allegro");
	Utils::check_initialized(al_install_keyboard(), "keyboard");
	Utils::check_initialized(al_init_font_addon(), "font addon");
	Utils::check_initialized(al_init_ttf_addon(), "true type font addon");
	Utils::check_initialized(al_init_image_addon(), "image addon");
	Utils::check_initialized(al_init_primitives_addon(), "primitives addon");

	_timer = al_create_timer(1.0 / c_FPS);
	Utils::check_created(_timer, "timer");

	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
	_display = al_create_display(500, 600); // przekazane parametry nie maj¹ znaczenia je¿eli okno jest pe³noekranowe
	
	//Skalowanie renderowanego obrazu do rozdzielczoœci wyœwietlacza:
	const float scale_factor_y = ((float)al_get_display_height(_display) / c_RENDER_HEIGHT);
	const float scale_factor_x = 16 / 9 * scale_factor_y;
	ALLEGRO_TRANSFORM scale_transform;
	al_identity_transform(&scale_transform);
	al_scale_transform(&scale_transform, scale_factor_x, scale_factor_y);
	al_use_transform(&scale_transform);

	_event_queue = al_create_event_queue();
	Utils::check_created(_event_queue, "event queue");
	al_register_event_source(_event_queue, al_get_keyboard_event_source());
	al_register_event_source(_event_queue, al_get_display_event_source(_display));
	al_register_event_source(_event_queue, al_get_timer_event_source(_timer));

	// przygotowanie do obs³ugi myszy:
	Utils::check_initialized(al_install_mouse(), "mouse");
	al_hide_mouse_cursor(_display);

	_game = std::make_unique<Game>();
	_game->Init();
}