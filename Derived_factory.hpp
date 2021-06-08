#include "Interface.hpp"
#include <dlfcn.h>
#include <memory>
#include <iostream>

class Derived_factory {
public:
    Derived_factory() {
        std::cout << "Derived_factory() opening ./libderived.so" << std::endl;
        handler = dlopen("./libderived.so", RTLD_NOW);
        if (! handler) {
            throw std::runtime_error(dlerror());
        }
        Reset_dlerror();
        creator = reinterpret_cast<Base_creator_t>(dlsym(handler, "create"));
        Check_dlerror();
    }

    std::unique_ptr<Base> create() const {
        std::cout << "Derived_factory::create()" << std::endl;
        return std::unique_ptr<Base>(creator());
    }

    ~Derived_factory() {
        std::cout << "~Derived_factory()" << std::endl;
        if (handler) {
            dlclose(handler);
        }
    }

private:
    void * handler = nullptr;
    Base_creator_t creator = nullptr;

    static void Reset_dlerror() {
        std::cout << "Derived_factory::Reset_dlerror()" << std::endl;
        dlerror();
    }

    static void Check_dlerror() {
        std::cout << "Derived_factory::Check_dlerror()" << std::endl;
        const char * dlsym_error = dlerror();
        if (dlsym_error) {
            throw std::runtime_error(dlsym_error);
        }
    }
};