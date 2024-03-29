#include <iostream>
#include <cmath>

bool cuadratic_has_real_roots(float a, float b, float c) {
    return (std::pow(b,2)-(4*a*c)) >= 0;
}

int main (void) {
    float a, b, c;

    std::cin >> a;
    std::cin >> b;
    std::cin >> c;

    std::cout << (cuadratic_has_real_roots(a,b,c) ? "Tiene raices reales\n" :
                 "No tiene raices reales\n");

    return 0;
}
