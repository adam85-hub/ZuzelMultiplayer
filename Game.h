#pragma once
#include <allegro5/allegro5.h>
#include "Consts.h"
#include "GameCommands.h"

class Game
{
public:
	virtual ~Game() {};
	virtual void Init();
	virtual void Update(KeyStatesTable) = 0;
	virtual void Render() const = 0;
	virtual void Handle_event(ALLEGRO_EVENT) {};
	virtual void Exit();

	bool Is_running();
protected:
	GameCommands _game_commands;
private:
	bool _is_running;
};

