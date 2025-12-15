#pragma once

#include <vector>
#include <stdexcept>
#include <utility>
#include <functional>
#include <type_traits>

#include "ICallable.h"

template<typename Ret, typename Obj, typename... Args>
class FunctionWrapper : public ICallable {
public:
    using MethodPtr = Ret (Obj::*)(Args...);

    FunctionWrapper(Obj& object, MethodPtr method)
        : target(object)
        , methodPtr(method) {}

    Container invoke(const std::vector<FunctionArgument>& args) override {
        return invokeImpl(args, std::index_sequence_for<Args...>{});
    }

private:
    Obj& target;
    MethodPtr methodPtr;

    template<std::size_t... I>
    Container invokeImpl(
        const std::vector<FunctionArgument>& args,
        std::index_sequence<I...>
    ) {
        if constexpr (std::is_void_v<Ret>) {
            std::invoke(
                methodPtr,
                target,
                container_cast<Args>(args[I].value)...
            );
            return Container();
        } else {
            Ret result = std::invoke(
                methodPtr,
                target,
                container_cast<Args>(args[I].value)...
            );
            return Container(result);
        }
    }
};
