#include <iostream>

unsigned int factorial_r(unsigned int n) {
    if((n == 0) || (n == 1))
        return 1;

    return n*factorial_r(n-1);
}

int main (void) {
    std::cout << factorial_r(5) << std::endl;
    return 0;
}
