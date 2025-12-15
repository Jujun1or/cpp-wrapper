#pragma once

#include <vector>
#include <stdexcept>

#include "ICallable.h"

template<typename Ret, typename Obj, typename... Args>
class FunctionWrapper : public ICallable {
public:
    using MethodPtr = Ret (Obj::*)(Args...);

    FunctionWrapper(Obj& object, MethodPtr method)
        : target(object)
        , methodPtr(method) {}

    Container invoke(const std::vector<FunctionArgument>&) override {
        throw std::logic_error("FunctionWrapper invoke not implemented yet");
    }

private:
    Obj& target;
    MethodPtr methodPtr;
};
