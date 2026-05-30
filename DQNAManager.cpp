#include "DQNAManager.h"
#include <memory>

DQNAssets DQNAManager::initAgent() {
	std::shared_ptr<FNN> mainFNN = std::make_shared<FNN>(), targetFNN = std::make_shared<FNN>();
	(*mainFNN).addInputLayer(21);
	(*mainFNN).addLayer(64);
	(*mainFNN).addLayer(64);
	(*mainFNN).addOutputLayer(2);
	(*mainFNN).setActivationFunction(AFunc::RELU);
	(*mainFNN).setOutputLayerActivationFunction(AFunc::LINEAR);

	(*targetFNN).addInputLayer(21);
	(*targetFNN).addLayer(64);
	(*targetFNN).addLayer(64);
	(*targetFNN).addOutputLayer(2);
	(*targetFNN).setActivationFunction(AFunc::RELU);
	(*targetFNN).setOutputLayerActivationFunction(AFunc::LINEAR);

	(*targetFNN).cloneWeights(*mainFNN);

	DQNHyperParams params{ 0.5, 1, 0.05, 0.05, 1000, 2, 20000 };

	std::shared_ptr<FNNDQNA> dqnAgent = std::make_shared<FNNDQNA>(params, mainFNN, targetFNN);

	return DQNAssets{ mainFNN, targetFNN, dqnAgent };
}

size_t DQNAssets::getAction(const std::shared_ptr<DQNState> state) {
	return dqnAgent->act(*state);
}
