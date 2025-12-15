#include "Engine.h"

void Engine::registerCommand(const std::string& name, ICallable* callable) {
    if (commands.find(name) != commands.end()) {
        throw std::runtime_error("command already registered");
    }
    commands[name] = callable;
}

Container Engine::execute(
    const std::string& name,
    const std::vector<FunctionArgument>& args
) {
    auto it = commands.find(name);
    if (it == commands.end()) {
        throw std::runtime_error("command not found");
    }

    return it->second->invoke(args);
}
