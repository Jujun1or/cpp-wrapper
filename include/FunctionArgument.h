#pragma once

#include <cstddef>
#include "Container.h"

struct FunctionArgument {
    std::size_t index{};
    Container value;

    FunctionArgument() = default;

    template<typename T>
    FunctionArgument(std::size_t idx, const T& v)
        : index(idx), value(v) {}

    FunctionArgument(const FunctionArgument&) = default;
    FunctionArgument(FunctionArgument&&) noexcept = default;

    FunctionArgument& operator=(const FunctionArgument&) = default;
    FunctionArgument& operator=(FunctionArgument&&) noexcept = default;
};
