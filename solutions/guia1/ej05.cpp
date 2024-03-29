#include <iostream>
#include <cmath>

int main (void) {
	double b, h, hipotenusa;

	std::cout << "* Calculadora de Triangulos *" << std::endl;
	std::cout << "Ingrese base del triangulo> " << std::flush;

	std::cin >> b;
	std::cout << "\033[1A\033[0KIngrese altura del triangulo> ";
	std::cin >> h;

	hipotenusa = std::sqrt(std::pow(b,2)+std::pow(h,2));

	std::cout << "\033[1A\033[0K    b = " << b << std::endl
		<< "    h = " << h << std::endl
		<< "perim = " << b+h+hipotenusa << std::endl
		<< "    s = " << (b*h)/2 << std::endl;

	return 0;
}
