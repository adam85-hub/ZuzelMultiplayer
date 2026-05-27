#pragma once
#include <vector>

struct State {
	State() = default;
	virtual ~State() = default;
	virtual std::vector<double> serialise() const;		//Returns serialized State data in a form of std::vector<double>
}; 