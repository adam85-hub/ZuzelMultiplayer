#include "AILearningGame.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>

#include <format>
#include "draw_polish_text.h"
#include "Consts.h"

AILearningGame::~AILearningGame() {
	delete[] _key_states;
	al_destroy_font(_font);
}

void AILearningGame::Init() {
	Game::Init();

	_race_scene = std::make_unique<RaceScene>(&_game_commands, 4, 3);

	_dqnAssets = DQNAManager::initAgent();

	_key_states = new unsigned char[ALLEGRO_KEY_MAX];
	_font = al_load_ttf_font(c_MAIN_FONT_PATH, c_RENDER_HEIGHT / 18, 0);
}

void AILearningGame::Update(KeyStatesTable _) {
	memset(_key_states, 0, ALLEGRO_KEY_MAX); // reset stanu klawiatury
	// zmiana stanu klawiatury
	_race_scene->Update(_key_states);
}

void AILearningGame::Render() const {
	Utils::draw_polish_text(_font, al_map_rgb(255, 255, 255), c_RENDER_WIDTH / 2, c_RENDER_HEIGHT / 2, Utils::ALIGN_CENTER_XY, "Learning...");
}

void AILearningGame::press_key(unsigned char key) {
	if (key >= ALLEGRO_KEY_MAX)
		throw std::out_of_range(std::format("Key must be between {} and {}", 0, ALLEGRO_KEY_MAX - 1));

	_key_states[key] = c_KEY_DOWN | c_KEY_PRESSED | c_KEY_SEEN;
}