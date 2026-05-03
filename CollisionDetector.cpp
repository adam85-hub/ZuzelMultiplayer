#include "CollisionDetector.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>



void CollisionDetector::displayDebugInfo(ALLEGRO_FONT* font, bool isColliding) {
    if (isColliding) {
        // Czerwony napis, gdy wykryto kontakt z band¹ [cite: 12]
        al_draw_text(font, al_map_rgb(255, 0, 0), 10, 10, 0, "KOLIZJA: TAK");
    }
    else {
        // Bia³y napis, gdy tor jest czysty
        al_draw_text(font, al_map_rgb(255, 255, 255), 10, 10, 0, "KOLIZJA: NIE");
    }
}

