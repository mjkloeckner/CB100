#include <iostream>

int main (void) {
	long input;

	std::cout << "Ingrese un número> " << std::flush;
	std::cin >> input;

	std::cout << "\033[1A\033[0KUsted ingreso `" << input << "`" << std::endl
		<< "El numero ingresado es "
		<< ((input == 0) ? "IGUAL" : ((input > 0) ? "MAYOR" : "MENOR"))
		<< " a CERO" << std::endl;

	return 0;
}
