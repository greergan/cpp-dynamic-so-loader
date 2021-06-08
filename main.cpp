#include "Derived_factory.hpp"
#include <memory>

int main() {
    Derived_factory factory;
    std::unique_ptr<Base> base = factory.create();
    base->foo();
}