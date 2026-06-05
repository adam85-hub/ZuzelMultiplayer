#pragma once
#include "DQN/FNN.hpp"
#include "DQN/FNNDQNA.hpp"
#include "SpeedwayState.hpp"

constexpr size_t HIDDEN_LAYERS_SIZE = 128;
constexpr size_t STATES_TO_PROCESS = 3;

struct DQNAssets {
	std::shared_ptr<FNN> main;
	std::shared_ptr<FNN> target;
	std::shared_ptr<FNNDQNA> dqnAgent;
	
	size_t getAction(const std::shared_ptr<DQNState> state);
	void update(const FNN& fnn, bool clearEpsilon = false);
};

class DQNAManager { //Deep-Q-Learning Agent Manager
public:
	static DQNAssets initAgent(); // initializes DQN agent
};