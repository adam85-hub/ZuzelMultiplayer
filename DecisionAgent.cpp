#include "DecisionAgent.hpp"
#include "DQNAManager.h"

DecisionAgent::DecisionAgent(FNN fnn, size_t actionsCount, double epsilon): actionsCount(actionsCount), epsilon(epsilon) {
	this->neuralNetwork = FNN();
	this->neuralNetwork.addInputLayer(PARAM_COUNT * STATES_TO_PROCESS);
	this->neuralNetwork.addLayer(HIDDEN_LAYERS_SIZE);
	this->neuralNetwork.addLayer(HIDDEN_LAYERS_SIZE);
	this->neuralNetwork.addOutputLayer(ACTION_COUNT);
	this->neuralNetwork.setActivationFunction(AFunc::L_RELU);
	this->neuralNetwork.setOutputLayerActivationFunction(AFunc::LINEAR);
	this->neuralNetwork.cloneWeights(fnn);
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
