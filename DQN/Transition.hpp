#pragma once
#include "DQNState.hpp"

struct Transition {
	std::vector<double> originalState;
	size_t action;
	double reward;
	std::vector<double> nextState;
	bool finished;
};