#pragma once
#include <allegro5/events.h>
#include <vector>

#include "Game.h"
#include "Scene.h"
#include "Consts.h"
#include "GameCommands.h"

// obiekt tej klasy zarz¹dza logik¹ gry, w tym np. wyœwietlanymi scenami oraz przechowuje jej stan
class NormalGame : public Game {
public:
	~NormalGame() override;
	void Init() override;
	void Update(KeyStatesTable) override;
	void Render() const override;

private:
	Scene* _current_scene = nullptr; // u¿ywam zwyk³ego wskaŸnika, poniewa¿ chcê mieæ precyzyjn¹ kontrolê nad d³ugoœci¹ ¿ycia tego obiektu
};