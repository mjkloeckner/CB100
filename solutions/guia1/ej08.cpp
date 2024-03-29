#include <iostream>

int main (void) {
	long input;

	std::cout << "Ingrese un número> " << std::flush;
	std::cin >> input;
	std::cout << "\033[1A\033[0KUsted ingreso `" << input << "`" << std::endl
		<< "El cual es un numero " << ((input % 2) ? "IMPAR" : "PAR")
		<< std::endl;

	return 0;
}
