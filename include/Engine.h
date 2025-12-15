#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <mutex>

#include "ICallable.h"
#include "FunctionArgument.h"

class Engine {
public:
    Engine() = default;

    void registerCommand(const std::string& name, ICallable* callable);
    Container execute(
        const std::string& name,
        const std::vector<FunctionArgument>& args
    );

private:
    std::unordered_map<std::string, ICallable*> commands;
    std::mutex mutex;
};
