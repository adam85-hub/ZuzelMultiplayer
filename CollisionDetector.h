#ifndef COLLISION_DETECTOR_H
#define COLLISION_DETECTOR_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

// Klasa odpowiedzialna za wykrywanie kolizji w grze "¯u¿el"
class CollisionDetector {
public:
    /**
     * Wyœwietla tekstow¹ informacjê o stanie kolizji na ekranie.
     * @param font WskaŸnik na za³adowan¹ czcionkê Allegro 5.
     * @param isColliding Flaga logiczna (true = kolizja, false = brak).
     */
    static void displayDebugInfo(ALLEGRO_FONT* font, bool isColliding);

    // Tutaj w przysz³oœci dodasz metodê sprawdzaj¹c¹, np.:
    // static bool checkBikeCollision(const BikeModel& bike);
};

#endif