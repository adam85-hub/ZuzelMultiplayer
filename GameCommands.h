#pragma once
#include "CommandDispatcher.h"

class Scene;

// zawiera obiekty CommandDispatcher
// s³u¿y do wywo³ywania okreœlonych zachowañ w obiekcie klasy Game
struct GameCommands {
	Utils::CommandDispatcher<bool> exit;
	Utils::CommandDispatcher<Scene*> switch_scene;
};