// El algoritmo utilizado para verificar que un numero es primo 
// es la Criba de Eratóstenes 
// https://es.wikipedia.org/wiki/Criba_de_Erat%C3%B3stenes

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cmath>

#define OUTPUT_FILE_PATH "primos.txt"
const unsigned int MAXIMO = 100000000;

void vector_discard_non_primes(std::vector<bool>& v) {
    v[0] = v[1] = false; // 0 y 1 no son primos
    for (size_t i = 2; i < std::sqrt(MAXIMO); ++i) {
        if(v[i]) {
            for (size_t j = i; j <= (MAXIMO/i); ++j) {
                v[i*j] = false;
            }
        }
    }
}

void vector_export_to_file_path(
        const std::vector<bool> v,
        std::ofstream& fp,
        unsigned int &primes_written) {

    primes_written = 0;
    for (size_t i = 2; i < v.size(); ++i) {
        if(v[i]) {
            fp << i << std::endl;
            primes_written++;
        }
    }
}

int main (void) {
    unsigned int ti, primes_found;
    double tt;
    std::ofstream fp;
    std::vector<bool> numeros(MAXIMO, true);

    ti = clock();

    vector_discard_non_primes(numeros);

    fp.open(OUTPUT_FILE_PATH);
    if (!fp.is_open()) {
        std::cerr << "ERROR: No se pudo abrir `" OUTPUT_FILE_PATH "`\n";
        return -1;
    }

    vector_export_to_file_path(numeros, fp, primes_found);
    fp.close();

    tt = (double(clock() - ti)) / CLOCKS_PER_SEC;

    std::cout.precision(2);
    std::string t_unit = "segundos";
    if(tt < 1) {
        tt *= 1000;
        t_unit.assign("ms");
        std::cout.precision(0);
    }

    std::cout << std::fixed
              << "Se encontraron `" << primes_found
              << "` numeros primos en `"
              << tt << "` " << t_unit << std::endl;

    return 0;
}
