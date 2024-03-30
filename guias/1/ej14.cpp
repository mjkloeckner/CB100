#include <iostream>

int main (void) {
    int fact;
    unsigned long res;

    std::cin >> fact;

    if(fact < 0) {
        std::cerr << "Math ERROR" << std::endl;
        return 1;
    }

    res = 1;
    for (size_t i = 1; i <= (long unsigned int)fact; i++) {
        res *= i;
    }

    std::cout << fact << "! = " << res << std::endl;

    return 0;
}
