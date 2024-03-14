#include <iostream>

int main (void) {
	char op;
	double a, b, res;

	std::cout << "Ingrese un número> " << std::flush;
	std::cin >> a;
	std::cout << "\033[1A\033[0KIngrese otro número> " << std::flush;
	std::cin >> b;
	std::cout << "\033[1A\033[0KIngrese operación a realizar [+, -, *, /]> "
		<< std::flush;
	std::cin >> op;

	switch(op) {
		case '+':
			res = a + b;
			break;
		case '-':
			res = a - b;
			break;
		case '*':
			res = a * b;
			break;
		case '/':
			res = a / b;
			break;
		default:
			std::cout << "Operación inválida\n";
			return -1;
	}

	std::cout << "\033[1A\033[0K`" << a << "` " << op << " `" 
		<< b << "` = " << res << std::endl;

	return 0;
}
