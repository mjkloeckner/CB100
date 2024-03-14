#include <iostream>
#include <string>

#define _USE_MATH_DEFINES
#include <cmath>

int main (void) {
	double rad, sup, vol;

	std::cout << "* Calculadora de Esferas *" << std::endl;
	std::cout << "Ingrese radio de la esfera> ";
	std::cin >> rad;

	std::cout << "\033[1A\033[0Kr = " << rad << std::endl
		<< "s = " << 4*M_PI*std::pow(rad, 2) << std::endl
		<< "v = " << (4.0f/3.0f)*M_PI*std::pow(rad, 3) << std::endl;

	return 0;
}
