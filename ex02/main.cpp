#include "Base.h"
#include "A.h"
#include "B.h"
#include "C.h"
#include <iostream>
#include <cstdlib>

Base *generate(void) {
    const int random = rand() % 3;
    switch (random) {
        case 0:
            std::cout << "\033[31m\033[1mA\033[0m\033[31m,\033[0m"; // 赤色でAを太字
            return new A();
        case 1:
            std::cout << "\033[34m\033[1mB\033[0m\033[34m,\033[0m"; // 青色でBを太字
            return new B();
        default:
            std::cout << "\033[33m\033[1mC\033[0m\033[33m,\033[0m"; // 黄色でCを太字
            return new C();
    }
}

void identify(Base *p) {
    if (dynamic_cast<A *>(p) != NULL) {
        std::cout << "\033[31mType of Base: \033[1mA\033[0m" << std::endl;
    }
    if (dynamic_cast<B *>(p) != NULL) {
        std::cout << "\033[34mType of Base: \033[1mB\033[0m" << std::endl;
    }
    if (dynamic_cast<C *>(p) != NULL) {
        std::cout << "\033[33mType of Base: \033[1mC\033[0m" << std::endl;
    }
}

void identify(Base &p) {
    try {
        const A &a = dynamic_cast<A &>(p);
        (void) a;
        std::cout << "\033[31mType of Base: \033[1mA\033[0m" << std::endl;
    } catch (...) {
    }
    try {
        const B &b = dynamic_cast<B &>(p);
        (void) b;
        std::cout << "\033[34mType of Base: \033[1mB\033[0m" << std::endl;
    } catch (...) {
    }
    try {
        const C &c = dynamic_cast<C &>(p);
        (void) c;
        std::cout << "\033[33mType of Base: \033[1mC\033[0m" << std::endl;
    } catch (...) {
    }
}


int main() {
    srand(time(NULL));
    Base *bases[10];
    for (int i = 0; i < 10; ++i) {
        bases[i] = generate();
    }
    std::cout << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << "---------------------" << std::endl;
        identify(bases[i]);
        identify(*bases[i]);
    }
    for (int i = 0; i < 10; ++i) {
        delete bases[i];
    }
    return 0;
}
