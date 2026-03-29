#pragma once
#include <string>
#include <stdexcept>

namespace Utils {
	class NotImplementedException : public std::logic_error
	{
	public:
		NotImplementedException(std::string what) : std::logic_error(what + std::string(" has not been yet implemented")) {};
	};
}
