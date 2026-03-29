#pragma once
#include "vec2.h"

// klasa bazowa wszystkich obiektów w grze
class GameObject {
public:
	GameObject() : position(0,0) {}
	GameObject(Utils::vec2 initial_position) : position(initial_position) {};

	Utils::vec2 position;
};