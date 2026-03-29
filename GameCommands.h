#pragma once
#include "CommandDispatcher.h"
#include "Scene.h"

// zawiera obiekty CommandDispatcher pozwalaj¹ce wywo³ywaæ okreœlone zachowanie w obiekcie klasy Game z obiektu _currentScene
struct GameCommands {
	Utils::CommandDispatcher<bool> exit;
	Utils::CommandDispatcher<Scene*> switch_scene;
};