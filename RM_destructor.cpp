#include "ResourceManager.h"

namespace Utils {
	ResourceManager::~ResourceManager() {
		for (ALLEGRO_FONT* font : _fonts) {
			al_destroy_font(font);
		}

		for (ALLEGRO_BITMAP* bitmap : _bitmaps) {
			al_destroy_bitmap(bitmap);
		}
	}
}