#include <iostream>

int main (void) {
    int a, b, *p, *q;

    a = 10;
    b = 20;
    p = &a;

    std::cout <<  a << std::endl;
    std::cout << &a << std::endl;
    std::cout <<  p << std::endl;
    std::cout << *p << std::endl;
    std::cout << &p << std::endl;

    q = &a;
    std::cout <<  q << std::endl;
    std::cout << *q << std::endl;
    std::cout << &q << std::endl;

    (*p)++;
    std::cout <<  a << std::endl;

    q = &b;
    *p = *q;

    std::cout <<  p << std::endl;
    std::cout << *p << std::endl;
    std::cout << &p << std::endl;

    p = q;
    std::cout <<  p << std::endl;
    std::cout << *p << std::endl;
    std::cout << &p << std::endl;

    return 0;
}
