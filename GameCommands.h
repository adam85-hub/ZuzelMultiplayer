#pragma once
#include "Command.h"

class Scene;
// zawiera obiekty Command
// służy do wywoływania okreœlonych zachowań w obiekcie klasy Game
struct GameCommands {
	Utils::Command<bool> exit;
	Utils::Command<Scene*> switch_scene;
};