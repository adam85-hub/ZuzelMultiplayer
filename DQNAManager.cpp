#include "DQNAManager.h"
#include <memory>

constexpr size_t HIDDEN_LAYERS_SIZE = 128;

DQNAssets DQNAManager::initAgent() {
	std::shared_ptr<FNN> mainFNN = std::make_shared<FNN>(), targetFNN = std::make_shared<FNN>();
	mainFNN->addInputLayer(PARAM_COUNT);
	mainFNN->addLayer(HIDDEN_LAYERS_SIZE);
	mainFNN->addLayer(HIDDEN_LAYERS_SIZE);
	mainFNN->addOutputLayer(ACTION_COUNT);
	mainFNN->setActivationFunction(AFunc::RELU);
	mainFNN->setOutputLayerActivationFunction(AFunc::LINEAR);

	targetFNN->addInputLayer(PARAM_COUNT);
	targetFNN->addLayer(HIDDEN_LAYERS_SIZE);
	targetFNN->addLayer(HIDDEN_LAYERS_SIZE);
	targetFNN->addOutputLayer(2);
	targetFNN->setActivationFunction(AFunc::RELU);
	targetFNN->setOutputLayerActivationFunction(AFunc::LINEAR);

	targetFNN->cloneWeights(*mainFNN);

	DQNHyperParams params{ 0.995, 1, 0.001, 0.025, 1000, ACTION_COUNT, 30000 };

	std::shared_ptr<FNNDQNA> dqnAgent = std::make_shared<FNNDQNA>(params, mainFNN, targetFNN);

	return DQNAssets{ mainFNN, targetFNN, dqnAgent };
}

size_t DQNAssets::getAction(const std::shared_ptr<DQNState> state) {
	return dqnAgent->act(*state);
}

void DQNAssets::update(const FNN& fnn) {
	main->cloneWeights(fnn);
	target->cloneWeights(fnn);
	auto params = dqnAgent->getParams();
	params.epsilon = params.epsilonMin;
	dqnAgent = std::make_shared<FNNDQNA>(params, main, target);
}