#include "Variable.h"

#include <optional>
#include <vector>


namespace Gaze{
	struct Parameter {
		Variable variable;
		std::optional<std::string> defaultValue;
	};

	struct Function {
		const std::string name;
		const Variable returnType;
		const std::vector<Parameter> parameters;
	};
}