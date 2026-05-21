#pragma once
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <functional>

class Countdown
{	
public:
	Countdown(int from);
	~Countdown();

	void Start();
	void Update();
	void Render() const;
	bool Has_ended() const;
	bool Has_race_started() const;

	void Execute_on_start(std::function<void()> to_execute);
private:
	int _from;
	int _current_count;
	double _start_time;
	bool _started = false;
	bool _ended = false;
	bool _race_started = false;

	std::function<void()> _to_execute_on_start;
	ALLEGRO_FONT* _font_countdown;
};

