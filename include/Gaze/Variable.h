#pragma once

#include <cstdint>
#include <string>

namespace Gaze{
struct VariableType {
	enum BaseType : uint8_t {
		Data = 0,
		Function_Ptr = 1,
	};
	enum Modifiers : std::uint16_t {
		Const = 1 << 0,
		Volatile = 1 << 1,
		Mutable = 1 << 2,

		Pointer = 1 << 3,
		Reference = 1 << 4,
		RVal_Ref = 1 << 5,
		Static = 1 << 6,
		Inline = 1 << 7,
	};
	BaseType type;
	Modifiers modifiers;
	std::string name;
};


struct Variable {
	const std::string name;
	const VariableType type;
};
}