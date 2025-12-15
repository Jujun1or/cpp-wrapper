#pragma once

#include <vector>
#include "Container.h"
#include "FunctionArgument.h"

class ICallable {
public:
    virtual ~ICallable() = default;

    virtual Container invoke(
        const std::vector<FunctionArgument>& args
    ) = 0;
};
