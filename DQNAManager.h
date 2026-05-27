#pragma once
#include "DQN/FNN.hpp"
#include "DQN/FNNDQNA.hpp"

struct DQNAssets {
	std::shared_ptr<FNN> main;
	std::shared_ptr<FNN> target;
	std::shared_ptr<FNNDQNA> dqnAgent;
};

class DQNAManager { //Deep-Q-Learning Agent Manager
public:
	static DQNAssets initAgent(); // initializes DQN agent
};