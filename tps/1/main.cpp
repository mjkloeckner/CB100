#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <string>

const unsigned int MAXIMO = 50000;

bool isPrime (long n) {
    if (n <= 1) {
        return false;
    }
    
    for (long i = 2; i < n; ++i) {
        if (!(n % i)) {
            return false;
        }
    }

    return true;
}

int main (void) {
    unsigned int ti, tf;
    double tt;
    std::ofstream fp;

    fp.open("primos.txt");
    if (!fp.is_open()) {
        std::cerr << "Unable to open file";
        return -1;
    }

    ti = clock();
    unsigned long i, j;
    for (i = j = 0; i < MAXIMO; ++i) {
        if (isPrime(i)) {
            fp << i << std::endl;
            j++;
        }
    }
    tf = clock();
    tt = (double(tf - ti)) / CLOCKS_PER_SEC;
    fp.close();
    

    std::string t_unit = "segundos";
    if(tt < 1) {
        tt *= 1000;
        t_unit.assign("ms");
    }

    std::cout.precision(2);
    std::cout << std::fixed
              << "Se econtraron `" << j 
              << "` numeros primos en `"
              << tt << "` " << t_unit << std::endl;

    return 0;
}
