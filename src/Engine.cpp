#include "Engine.h"

void Engine::registerCommand(const std::string& name, ICallable* callable) {
    std::lock_guard<std::mutex> lock(mutex);

    if (commands.find(name) != commands.end()) {
        throw std::runtime_error("command already registered");
    }

    commands[name] = callable;
}

Container Engine::execute(
    const std::string& name,
    const std::vector<FunctionArgument>& args
) {
    ICallable* callable = nullptr;

    {
        std::lock_guard<std::mutex> lock(mutex);

        auto it = commands.find(name);
        if (it == commands.end()) {
            throw std::runtime_error("command not found");
        }

        callable = it->second;
    }

    return callable->invoke(args);
}
