#include <iostream>

int main (void) {
    long input, res;

    res = 0;
    do {
        std::cin >> input;
        std::cout << "\033[1A\033[0K"; // Borra el numero ingresado
        std::cout << input << " " << input + res << std::endl;
        res += input;
    } while (input != 0);

    return 0;
}
