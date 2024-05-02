// Fast multiplication of large integers using Karatsuba algorithm
// https://en.wikipedia.org/wiki/Karatsuba_algorithm
// https://www.youtube.com/watch?v=k_j5TAPQf7k
// https://www.youtube.com/watch?v=yWI2K4jOjFQ

#include <iostream>
#include <cmath>

long max(long x, long y) {
    return (x > y) ? x : y;
}

unsigned int size_base10(long n) {
    return (abs(n) <= 9) ? 1 : (1 + size_base10(n/10));
}

long shift_right_by_base10(long n, unsigned int m) {
    return (long)(n / std::pow(10, m));
}

long karatsuba(long x, long y) {
    if((x < 10) || (y < 10))
        return x*y; // fall back to traditional multiplicatio

    unsigned int n = max(size_base10(x), size_base10(y));

    long a = shift_right_by_base10(x, (n/2));
    long b = (x % (long)pow(10, n/2));

    long c = shift_right_by_base10(y, (n/2));
    long d = (y % (long)pow(10, n/2));

    long ac = karatsuba(a, c);
    long bd = karatsuba(b, d);
    long ad_plus_bc = (karatsuba(a+b, c+d)-ac-bd);

    return ((ac*pow(10, (n/2)*2)) + (ad_plus_bc*pow(10, n/2)) + bd);
}

int main (void) {
    std::cout << karatsuba(146123, 352120) << std::endl;
    return 0;
}
