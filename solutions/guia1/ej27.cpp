// https://en.wikipedia.org/wiki/Least_common_multiple
// https://en.wikipedia.org/wiki/Greatest_common_divisor
// https://en.wikipedia.org/wiki/Euclidean_algorithm

#include <iostream>

int find_gcd(int a, int b) {
    if(!b)
        return a;

    return find_gcd(b, a % b);
}

int find_lcm(int a, int b) {
    return (a * b) / find_gcd(a, b);
}

int main (void) {
    int a, b, lcm, gcd;

    std::cin >> a;
    std::cin >> b;

    lcm = find_lcm(a,b);
    gcd = find_gcd(a,b);

    std::cout << "a=" << a
              << "\tb=" << b << std::endl
              << "lcm=" << lcm << std::endl
              << "gcd=" << gcd << std::endl;
    return 0;
}
