#include <filesystem>

#include "Variable.h"
#include "Structure.h"
#include "Function.h"

namespace Gaze{
    struct File{

        std::vector<Variable> variables{};
        std::vector<Function> functions{};
        std::vector<Structure> structures{};
    };
    struct Folder{

    };


    struct ReflectedData{

    };
}