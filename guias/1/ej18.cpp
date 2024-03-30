#include <iostream>

int main (void) {
    int a, b;
    unsigned int c; // c=a*b

    std::cout << "a> ";
    std::cin >> a;
    std::cout << "\033[1A\033[2K"; // Borra el caracter ingresado 
    if (std::cin.fail()) {
        std::cerr << "Solo se permite ingresar números\n";
        return -1;
    }

    std::cout << "b> ";
    std::cin >> b;
    std::cout << "\033[1A\033[2K"; // Borra el caracter ingresado 
    if (std::cin.fail()) {
        std::cerr << "Solo se permite ingresar números\n";
        return -1;
    }

    c = 0;
    for(size_t i = 0; i < b; ++i) {
        c += a;
    }

    std::cout << a << "*" << b << "=" << c << std::endl;
    return 0;
}
