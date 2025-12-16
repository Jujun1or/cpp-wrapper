#pragma once

#include <memory>
#include <typeinfo>
#include <stdexcept>

class Container {
private:
    struct Base {
        virtual ~Base() = default;
        virtual std::unique_ptr<Base> clone() const = 0;
        virtual const std::type_info& type() const = 0;
    };

    template<typename T>
    struct Model final : Base {
        T data;

        explicit Model(const T& value)
            : data(value) {}

        std::unique_ptr<Base> clone() const override {
            return std::make_unique<Model<T>>(data);
        }

        const std::type_info& type() const override {
            return typeid(T);
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

    bool empty() const {
        return storage == nullptr;
    }

    template<typename T>
    T get() const {
        if (!storage) {
            throw std::runtime_error("Container is empty");
        }

        if (storage->type() != typeid(T)) {
            throw std::runtime_error("Container type mismatch");
        }

        return static_cast<Model<T>*>(storage.get())->data;
    }
};

template<typename T>
T container_cast(const Container& c) {
    return c.get<T>();
}
