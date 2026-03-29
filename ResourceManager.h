#pragma once
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

#include <string>
#include <vector>

namespace Utils {

template<typename T>
concept Resource = std::is_same_v<T, ALLEGRO_FONT> || std::is_same_v<T, ALLEGRO_BITMAP>;

// Zarz¹dza zasobami, które bêd¹ dostêpne tak d³ugo jak sam obiekt ResourceManager. Do u¿ycia tylko je¿eli po usuniêciu obiektu nie bêdziemy ju¿ potrzebowaæ dodanych do œledzenia zasobów
class ResourceManager {
public:
	// Dodaje zasób resource do "œledzonych zasobów", dziêki czemu zostanie on zwolniony w momencie uruchomienia destruktora obiektu klasy ResourceManager
	template<Resource T> void Track_resource(T* resource);
	// zwalnia wszystkie dodane zasoby
	~ResourceManager(); 
private:
	std::vector<ALLEGRO_FONT*> _fonts;
	std::vector<ALLEGRO_BITMAP*> _bitmaps;
};

}
