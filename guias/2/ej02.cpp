#include <iostream>

int main(void) {
    int a, b, *p, **pp;
    char c, d, *q;

    a = 1;
    b = 2;
    c = 'A';
    d = 'E';

    std::cout << "  &a: " << &a << std::endl;
    std::cout << "  &b: " << &b << std::endl;
    std::cout << "  &c: " << &c << std::endl;
    std::cout << "  &d: " << &d << std::endl;

    p = &a;
    *p = 87;

    q = &c;
    *q = d;

    std::cout << "   p: " <<  p << std::endl;
    std::cout << "  &p: " << &p << std::endl;
    std::cout << "  *p: " << *p << std::endl;

    std::cout << "   q: " <<  q << std::endl;
    std::cout << "  &q: " << &q << std::endl;
    std::cout << "  *q: " << *q << std::endl;

    q = (char *)p;
    pp = &p;
    *pp = &b;
    std::cout << "   p: " << p << std::endl;

    std::cout << "  pp: " <<   pp << std::endl;
    std::cout << " &pp: " <<  &pp << std::endl;
    std::cout << " *pp: " <<  *pp << std::endl;
    std::cout << "**pp: " << **pp << std::endl;

    return 0;
}
