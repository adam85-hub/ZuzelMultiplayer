#include "Countdown.h"
#include <cmath>
#include <allegro5/allegro_ttf.h>

#include "Consts.h"
#include "draw_polish_text.h"

Countdown::Countdown(int from) :
	_from(from),
	_start_time(-1),
	_current_count(-1)
{
	_font_countdown = al_load_ttf_font(c_MAIN_FONT_PATH, c_RENDER_HEIGHT / 5, 0);
}

Countdown::~Countdown() {
	al_destroy_font(_font_countdown);
}

void Countdown::Start() {
	_started = true;
	_start_time = al_get_time();
	_current_count = _from;
}

void Countdown::Update() {
	if (!_started || _ended)
		return;

	double time_elapsed = al_get_time() - _start_time;
	_current_count = _from - std::floor(time_elapsed);

	if (time_elapsed > _from)
		_race_started = true;
	if (time_elapsed > _from + 1)
		_ended = true;
}

void Countdown::Render() const {
	if (!_started || _ended)
		return;

	std::string text = std::to_string(_current_count);
	if (_current_count == 0) {
		text = "Start!";
	}

	Utils::draw_polish_text(_font_countdown, al_map_rgb(255, 255, 255), c_RENDER_WIDTH / 2, c_RENDER_HEIGHT / 2, Utils::ALIGN_CENTER_XY, text);
}

bool Countdown::Has_ended() const {
	return _ended;
}

bool Countdown::Has_race_started() const {
	return _race_started;
}