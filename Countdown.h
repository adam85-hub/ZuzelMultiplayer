#pragma once
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <functional>

#include "Timer.h"

class Countdown
{	
public:
	Countdown(int from);
	~Countdown();

	void Start();
	void Update();
	void Render() const;
	void Pause();
	void Unpause();
	bool Has_ended() const;
	bool Has_race_started() const;

	void Execute_on_start(std::function<void()> to_execute);
private:
	Timer _timer;

	int _from;
	int _current_count;
	bool _started = false;
	bool _ended = false;
	bool _race_started = false;

	std::function<void()> _to_execute_on_start;
	ALLEGRO_FONT* _font_countdown;
};

