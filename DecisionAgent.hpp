#pragma once

#include <vector>
#include "DQN/FNN.hpp"

class DecisionAgent { // Lightweight version of DQN Agent. Small class for decision-making using a preloaded neural network
public:
	DecisionAgent(FNN fnn, size_t actionsCount, double epsilon = 0.05);
	size_t act(const std::vector<double>& state, bool getConsoleOutput = false);
private:
	FNN neuralNetwork;
	double epsilon;
	size_t actionsCount;
};