#include <iostream>

int main (void) {
    unsigned long first_digit;

    std::cin >> first_digit;

    for (size_t i = 0; i < 20; ++i)
        std::cout << first_digit + i << std::endl;

    return 0;
}
