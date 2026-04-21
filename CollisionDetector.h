#ifndef COLLISION_DETECTOR_H
#define COLLISION_DETECTOR_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

class CollisionDetector {
public:

    static void displayDebugInfo(ALLEGRO_FONT* font, bool isColliding);

};

#endif