#include "EngineTests.h"

#include <iostream>
#include <cassert>
#include <string>

#include "Engine.h"
#include "FunctionWrapper.h"
#include "FunctionArgument.h"
#include "Container.h"

namespace {

class Calculator {
public:
    int sum(int a, int b) {
        return a + b;
    }
};

class TextBuffer {
public:
    void append(const std::string& s) {
        data += s;
    }
    std::string data;
};

class Mixer {
public:
    double combine(int a, double b, const std::string& c) {
        return a + b + static_cast<double>(c.size());
    }
};

void testSum() {
    Calculator calc;
    FunctionWrapper<int, Calculator, int, int> wrapper(
        calc,
        &Calculator::sum
    );

    Engine engine;
    engine.registerCommand("sum", &wrapper);

    Container result = engine.execute(
        "sum",
        {
            {0, 2},
            {1, 3}
        }
    );

    assert(container_cast<int>(result) == 5);
    std::cout << "[PASSED] testSum" << std::endl;
}

void testVoidMethod() {
    TextBuffer buffer;
    FunctionWrapper<void, TextBuffer, const std::string&> wrapper(
        buffer,
        &TextBuffer::append
    );

    Engine engine;
    engine.registerCommand("append", &wrapper);

    engine.execute("append", { {0, std::string("Hello")} });
    engine.execute("append", { {0, std::string(" World")} });

    assert(buffer.data == "Hello World");
    std::cout << "[PASSED] testVoidMethod" << std::endl;
}

void testMixedTypes() {
    Mixer mixer;
    FunctionWrapper<double, Mixer, int, double, const std::string&> wrapper(
        mixer,
        &Mixer::combine
    );

    Engine engine;
    engine.registerCommand("combine", &wrapper);

    Container result = engine.execute(
        "combine",
        {
            {0, 3},
            {1, 2.5},
            {2, std::string("abcd")}
        }
    );

    assert(container_cast<double>(result) == 9.5);
    std::cout << "[PASSED] testMixedTypes" << std::endl;
}

}

void EngineTests::runAll() {
    std::cout << "=== Test session started ===" << std::endl;

    testSum();
    testVoidMethod();
    testMixedTypes();

    std::cout << "=== All tests passed successfully ===" << std::endl;
}
