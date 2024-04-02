// Taken from /guias/1/ej27.cpp
// https://en.wikipedia.org/wiki/Greatest_common_divisor

#include <iostream>

int find_gcd(int a, int b) {
    if(!b)
        return a;

    return find_gcd(b, a % b);
}


int main (void) {
    std::cout << find_gcd(8, 12) << std::endl;

    return 0;
}
