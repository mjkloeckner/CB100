#include <iostream>
#include <string>

int main (void) {
	std::string input;

	std::cout << "Ingrese su nombre: ";
	std::getline(std::cin, input);
	std::cout << "\033[1A\033[0KBienvenido " << input << "!" << std::endl;

	return 0;
}
