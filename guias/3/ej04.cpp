// https://en.wikipedia.org/wiki/Fibonacci_sequence

#include <iostream>

int fibonacci_r(int x) {
    return (x <= 1) ? x : fibonacci_r(x-1) + fibonacci_r(x-2);
}

int main (void) {
    for(size_t i = 0; i <= 10; ++i)
        std::cout << fibonacci_r(i) << std::endl;

    return 0;
}
