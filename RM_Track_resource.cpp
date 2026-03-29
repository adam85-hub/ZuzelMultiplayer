#include "ResourceManager.h"
#include "NotImplementedException.h"

#include <type_traits>

namespace Utils {
	template <>
	void ResourceManager::Track_resource<ALLEGRO_FONT>(ALLEGRO_FONT* font) {
		_fonts.push_back(font);
	}

	template <>
	void ResourceManager::Track_resource<ALLEGRO_BITMAP>(ALLEGRO_BITMAP* bitmap) {
		_bitmaps.push_back(bitmap);
	}

	template<Resource T>
	void ResourceManager::Track_resource(T* resource) {
		throw NotImplementedException("Function ResourceManager::Track_resource not implemented for type " + typeid(T).name);
	}
}