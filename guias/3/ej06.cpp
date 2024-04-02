// https://en.wikipedia.org/wiki/Ackermann_function

#include <iostream>

unsigned int ackerman(unsigned int m, unsigned int n) {
    if(!m)
        return n + 1;

    if(!n)
        return ackerman(m-1, 1);

    return ackerman(m-1, ackerman(m, n-1));
}


int main (void) {
    std::cout << ackerman(3, 3) << std::endl;

    return 0;
}
