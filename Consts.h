#pragma once
#include <allegro5/allegro5.h>

using KeyStatesTable = unsigned char*;

// wszystkie zdefiniowane tutaj sta³e maj¹ mieæ prefix c_

constexpr int c_RENDER_HEIGHT = 1080;
constexpr int c_RENDER_WIDTH = 1920;
constexpr int c_FPS = 60;

#define c_MAIN_FONT_PATH "Assets/Jersey10_Regular.ttf"

#define c_KEY_SEEN 1
#define c_KEY_DOWN 2
#define c_KEY_PRESSED 4
#define c_KEY_PRESSED_HANDLED 8
