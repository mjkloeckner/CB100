#include <iostream>

// by reference
void numbers_swap_r(int &a, int &b) {
    a += b;
    b = a - b;
    a -= b;
}


// by pointers
void numbers_swap_p(int *a, int *b) {
	*a += *b;
	*b  = *a - *b;
	*a -= *b;
}

void numbers_print(int a, int b) {
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
}

int main (void) {
    int a, b;

    a = 1;
    b = 2;

    numbers_print(a, b);
    std::cout << "// Swap by reference" << std::endl;
    numbers_swap_r(a, b);
    numbers_print(a, b);

    std::cout << "// Swap by pointer" << std::endl;
    numbers_swap_p(&a, &b);
    numbers_print(a, b);

    return 0;
}
