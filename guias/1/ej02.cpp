#include <iostream>
#include <iomanip>

int main (void) {
	int a, b;

	std::cin >> a;
	std::cout << "\033[1A\033[0Ka = " << a << std::endl; 

	std::cin >> b;
	std::cout << "\033[1A\033[0Kb = " << b << std::endl; 

	std::cout << "a+b = " << std::setw(2) << a + b << std::endl;
	std::cout << "a-b = " << std::setw(2) << a - b << std::endl;
	std::cout << "a*b = " << std::setw(2) << a * b << std::endl;
	std::cout << "a/b = " << std::setw(2) << a / b << std::endl;

	return 0;
}
