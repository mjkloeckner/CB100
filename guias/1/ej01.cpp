#include <iostream>

int main(void) {
	int input;

	std::cin >> input;

	// https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
	std::cout << "\033[1A"; 
	std::cout << "Usted ingresó: " << input << std::endl;

	return 0;
}
