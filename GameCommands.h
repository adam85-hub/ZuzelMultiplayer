#pragma once
#include "Command.h"
#include "Scene.h"

// zawiera obiekty Command
// s³u¿y do wywo³ywania okreœlonych zachowañ w obiekcie klasy Game
struct GameCommands {
	Utils::Command<bool> exit;
	Utils::Command<Scene*> switch_scene;
};