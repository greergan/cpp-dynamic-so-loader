#include "Interface.hpp"
#include <iostream>

class Derived: public Base {
public:
    void foo() const override {
        std::cout << "derived::foo() called" << std::endl;
    }
};

extern "C" {
Base * create() {
    return new Derived;
}
}
