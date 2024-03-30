#include <iostream>
#include <vector>

bool is_prime(unsigned int n) {
    std::vector<bool> v(n + 1, true);

    if((n == 0) || (n == 1))
        return false;

    for (size_t i = 2; i*i < n; ++i)
        if(v[i])
            for (size_t j = i; j <= (n/i); ++j)
                v[i*j] = false;

    return v[n];
}

int main (void) {
    unsigned int n;

    std::cout << "Ingrese un valor entero> ";
    std::cin >> n;

    std::cout << (is_prime(n) ? "Es primo\n" : "No es primo\n");
    return 0;
}
