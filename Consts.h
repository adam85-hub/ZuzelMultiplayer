#pragma once
#include <allegro5/allegro5.h>
#include <string>
#include "vec2.h"

using KeyStatesTable = unsigned char*;

// wszystkie zdefiniowane tutaj sta³e maj¹ mieæ prefix c_

constexpr int c_RENDER_HEIGHT = 1080;
constexpr int c_RENDER_WIDTH = 1920;
constexpr int c_FPS = 60;
const Utils::vec2 c_MIDDLE = Utils::vec2(c_RENDER_WIDTH / 2.f, c_RENDER_HEIGHT / 2.f);

const std::string c_PLAYER_NAME[4] = {"Czerwony", "Zielony", "Niebieski", "¯ó³ty"};
const ALLEGRO_COLOR c_PLAYER_COLOR[4] = { al_map_rgb(255, 43, 0), al_map_rgb(56, 176, 25), al_map_rgb(0, 115, 219), al_map_rgb(194, 205, 0) };


#define c_MAIN_FONT_PATH "Assets/Jersey10_Regular.ttf"

#define c_KEY_SEEN 1
#define c_KEY_DOWN 2
#define c_KEY_PRESSED 4
#define c_KEY_PRESSED_HANDLED 8
