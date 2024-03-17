#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <vector>
#include <cmath>

#define OUTPUT_FILE_PATH "primos.txt"
const unsigned int MAXIMO = 100000000;

int main (void) {
    unsigned int ti, tf;
    double tt;
    std::ofstream fp;

    ti = clock();

    unsigned long i, j;
    std::vector<bool> numeros(MAXIMO);
    std::fill(numeros.begin(), numeros.end(), true);
    for (i = 2; i < std::sqrt(MAXIMO); ++i) {
        if(numeros[i] == true) {
            for (j = i; j <= (MAXIMO/i); ++j)
                numeros[i*j] = false;
        }
    }

    fp.open(OUTPUT_FILE_PATH);
    if (!fp.is_open()) {
        std::cerr << "ERROR: No se pudo abrir `" OUTPUT_FILE_PATH << "`";
        return -1;
    }

    for (i = 2, j = 0; i < numeros.size(); ++i) {
        if(numeros[i]) {
            fp << i << std::endl;
            j++;
        }
    }

    fp.close();

    tf = clock();
    tt = (double(tf - ti)) / CLOCKS_PER_SEC;

    std::cout.precision(2);
    std::string t_unit = "segundos";
    if(tt < 1) {
        tt *= 1000;
        t_unit.assign("ms");
        std::cout.precision(0);
    }

    std::cout << std::fixed
              << "Se econtraron `" << j 
              << "` numeros primos en `"
              << tt << "` " << t_unit << std::endl;

    return 0;
}
