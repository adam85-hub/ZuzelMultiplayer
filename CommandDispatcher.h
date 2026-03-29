#pragma once
#include <vector>
#include <functional>
#include <type_traits>

namespace Utils {
	template<typename T>
	concept FunctionParameter = not std::is_void_v<T>;

	template <FunctionParameter T>
	class CommandDispatcher {
		using CommandFn = std::function<void(T)>;

		std::vector<CommandFn> _commandFunctions;
	public:
		void Implement(CommandFn commandFn) {
			_commandFunctions.push_back(commandFn);
		}

		void Execute(T data) {
			for (CommandFn commandFn : _commandFunctions) {
				commandFn(data);
			}
		}
	};
}