#include "DecisionAgent.hpp"

DecisionAgent::DecisionAgent(FNN fnn, size_t actionsCount, double epsilon): actionsCount(actionsCount), epsilon(epsilon) {
	this->neuralNetwork = fnn;
}

size_t DecisionAgent::act(const std::vector<double>& state, bool getConsoleOutput) {
	double rand = mfuncs::getRandomDouble(0.0, 1.0);
	if (rand <= epsilon)
		return static_cast<size_t>(mfuncs::getRandomInteger(0, actionsCount - 1));
	neuralNetwork.process(state);
	std::vector<double> qValues = neuralNetwork.getOutput();
	size_t action = mfuncs::maxIndex(qValues);
	if (getConsoleOutput) {
		for (size_t i{}; i < actionsCount; i++) std::cout << " | Q_" << i << ": " << qValues[i];
		std::cout << " | ACTION: " << action << "\n";
	}
	return action;
}
