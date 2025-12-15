#pragma once

#include <memory>

class Container {
private:
    struct Base {
        virtual ~Base() = default;
        virtual std::unique_ptr<Base> clone() const = 0;
    };

    template<typename T>
    struct Model final : Base {
        T data;

        explicit Model(const T& value)
            : data(value) {}

        std::unique_ptr<Base> clone() const override {
            return std::make_unique<Model<T>>(data);
        }
    };

    std::unique_ptr<Base> storage;

public:
    Container() = default;

    template<typename T>
    Container(const T& value)
        : storage(std::make_unique<Model<T>>(value)) {}

    Container(const Container& other)
        : storage(other.storage ? other.storage->clone() : nullptr) {}

    Container(Container&& other) noexcept = default;

    Container& operator=(const Container& other) {
        if (this == &other) {
            return *this;
        }
        storage = other.storage ? other.storage->clone() : nullptr;
        return *this;
    }

    Container& operator=(Container&& other) noexcept = default;
};
