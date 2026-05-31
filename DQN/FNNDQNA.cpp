#include "FNNDQNA.hpp"

FNNDQNA::FNNDQNA(
	const DQNHyperParams& dqnparams,
	std::shared_ptr<FNN> main,
	std::shared_ptr<FNN> target
): params(dqnparams), main(std::move(main)), target(std::move(target)) {}

DQNHyperParams FNNDQNA::getParams() const { return params; }

size_t FNNDQNA::act(const DQNState& state) {
	double rand = mfuncs::getRandomDouble(0.0, 1.0);
	if (rand <= params.epsilon)
		return static_cast<size_t>(mfuncs::getRandomInteger(0, params.actionsCount - 1));
	main->process(state.serialise());
	std::vector<double> qValues = main->getOutput();
	return mfuncs::maxIndex(qValues);

}

void FNNDQNA::remember(const std::vector<double>& state, size_t action, double reward,
	const std::vector<double>& nextState, bool finished) {

	memory.push_back({ state, action, reward, nextState, finished });

	if (memory.size() > params.memoryCapacity) {
		memory.pop_front();
	}
}

void FNNDQNA::replayLearn() { // Replay previous experiences and learn on the mistakes
	if (memory.size() < params.batchSize) return; //if memory is smaller than the minimum amount to learn, return. 
	std::cout << "Memory size: " << memory.size() << "\n";
	auto batch = getMemoryBatch(); // get random batch of previous memories

	for (const Transition& transition : batch) {
		double targetValue = getTargetValue(transition);

		auto currentQValues = getCurrentQValues(transition.originalState);
		currentQValues[transition.action] = targetValue;

		FNNBackpropA::trainFNNStep(main, transition.originalState, currentQValues, learningFactor, true);
	}
	if (params.epsilon > params.epsilonMin) params.epsilon *= params.epsilonDecayRate;
}

std::vector<Transition> FNNDQNA::getMemoryBatch() {
	std::vector<Transition> batch;
	auto indexVec = mfuncs::getNRandomUniqueIntegers(0, memory.size(), params.batchSize);
	for (auto index : indexVec)
		batch.push_back(memory[index]);
	return batch;
}

void FNNDQNA::updateTargetNN() {
	(*target).cloneWeights(*main);
}

double FNNDQNA::getTargetValue(const Transition& transition) {
	double targetValue = transition.reward;
	if (!transition.finished) {
		(*target).process(transition.nextState);
		std::vector<double> nextQValues = (*target).getOutput();
		double maxNextQ = mfuncs::max(nextQValues);
		targetValue += params.gamma * maxNextQ;
	}
	return targetValue;
}

std::vector<double> FNNDQNA::getCurrentQValues(const std::vector<double>& inputVec) {
	(*main).process(inputVec);
	return (*main).getOutput();
}