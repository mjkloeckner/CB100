#include <iostream>

// If called without an exponent value it returns the number squared
int pow_r(int x) {
    return x*x;
}

int pow_r(int x, int y) {
    if(y == 0)
        return 1;

    return x*pow_r(x, y-1);
}

int main (void) {
    std::cout << pow_r(2, 8) << std::endl;
    return 0;
}
