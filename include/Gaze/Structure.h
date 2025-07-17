#include "Variable.h"
#include "Function.h"

namespace Gaze{
	struct Class {
		const std::string name;

		const std::vector<Variable> private_variables;
		const std::vector<Function> private_functions;

		const std::vector<Variable> protected_variables;
		const std::vector<Function> protected_functions;

		const std::vector<Variable> public_variables;
		const std::vector<Function> public_functions;
	};
}