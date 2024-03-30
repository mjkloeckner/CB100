#include <iostream>

int main (void) {
	long a, b;

	std::cout << "Ingrese un número> " << std::flush;
	std::cin >> a;
	std::cout << "\033[1A\033[0KIngrese otro número> " << std::flush;
	std::cin >> b;

	std::cout << "\033[1A\033[0KUsted ingreso `" << a << "` y `" 
		<< b << "`" << std::endl;

	std::cout << a << (a > b ? " > " : " < ") << b << std::endl;

	return 0;
}
