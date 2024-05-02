// Fast multiplication of large integers
// https://en.wikipedia.org/wiki/Karatsuba_algorithm
// https://www.youtube.com/watch?v=k_j5TAPQf7k
// https://www.youtube.com/watch?v=yWI2K4jOjFQ

#include <iostream>
#include <cmath>

unsigned int size_base10(long n) {
    return (abs(n) <= 9) ? 1 : (1 + size_base10(n/10));
}

long shift_right_by_base10(long n, unsigned int m) {
    return (long)(n / std::pow(10, m));
}

long karatsuba(long x, long y) {
    if((x < 10) || (y < 10)) {
        std::cout << x*y << std::endl;
        return x*y; // fall back to traditional multiplication
    }

    unsigned int n1 = size_base10(x);
    unsigned int n2 = size_base10(y);

    long a = shift_right_by_base10(x, (n1/2));
    long b = (x % (long)pow(10, n1/2));

    long c = shift_right_by_base10(y, (n2/2));
    long d = (y % (long)pow(10, n2/2));

    long ac = karatsuba(a, c);
    long bd = karatsuba(b, d);
    long ad_plus_bc = (karatsuba(a+b, c+d)-ac-bd);

    long res = ((ac*pow(10, (n2/2)*2)) + (ad_plus_bc*pow(10, n2/2)) + bd);
    std::cout << res << std::endl;
    return res;
}

int main (void) {
    std::cout << karatsuba(146123, 352120) << std::endl;
    return 0;
}
