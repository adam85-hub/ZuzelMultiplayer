#pragma once
#include <allegro5/events.h>
#include <vector>

#include "Scene.h"
#include "Consts.h"
#include "GameCommands.h"

// obiekt tej klasy zarz¹dza logik¹ gry, w tym np. wyœwietlanymi scenami oraz przechowuje jej stan
class Game {
public:
	~Game();
	void Init();
	void Update(KeyStatesTable);
	void Render();
	void Handle_event(ALLEGRO_EVENT);
	void Exit();

	bool Is_running();

private:
	Scene* _currentScene = nullptr; // u¿ywam zwyk³ego wskaŸnika, poniewa¿ chcê mieæ precyzyjn¹ kontrolê nad d³ugoœci¹ ¿ycia tego obiektu
	bool _isRunning;

	GameCommands _game_commands;
};