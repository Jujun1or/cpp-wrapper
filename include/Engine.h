#pragma once

#include <string>
#include <vector>

class Engine {
public:
    Engine() = default;

    void registerCommand(const std::string& name, void* callable);
    void execute(const std::string& name);
};
