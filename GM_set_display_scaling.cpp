#include "GameManager.h"
#include "check_functions.h"

void GameManager::set_display_scaling() {
	Utils::check_created(_display, "display");

	float scale_factor = 1, translate_x = 0, translate_y = 0;
	float display_h = al_get_display_height(_display);
	float display_w = al_get_display_width(_display);

	if (display_w / display_h > 16.f / 9) {
		scale_factor = display_h / c_RENDER_HEIGHT;

		float rendered_w = scale_factor * c_RENDER_WIDTH;
		translate_x = (display_w - rendered_w)/2;
	}
	else {
		scale_factor = display_w / c_RENDER_WIDTH;

		float rendered_h = scale_factor * c_RENDER_HEIGHT;
		translate_y = (display_h - rendered_h) / 2;
	}

	ALLEGRO_TRANSFORM scale_transform;
	al_identity_transform(&scale_transform);
	al_scale_transform(&scale_transform, scale_factor, scale_factor);
	al_translate_transform(&scale_transform, translate_x, translate_y);

	al_use_transform(&scale_transform);
}