// El algoritmo utilizado para verificar que un numero es primo 
// es la Criba de Eratóstenes 
// https://es.wikipedia.org/wiki/Criba_de_Erat%C3%B3stenes

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

#define OUTPUT_FILE_PATH "primos.txt"
const unsigned int MAXIMO = 100000000;

void vectorDiscardNonPrimes(std::vector<bool>& v) {
    v[0] = v[1] = false; // 0 y 1 no son primos
    for (size_t i = 2; i*i < MAXIMO; ++i) {
        if(v[i]) {
            for (size_t j = i; j <= (MAXIMO/i); ++j) {
                v[i*j] = false;
            }
        }
    }
}

void vectorExportToFilePath(
        const std::vector<bool> v,
        std::ofstream& fp,
        unsigned int &primesWritten) {

    primesWritten = 0;
    for (size_t i = 2; i < v.size(); ++i) {
        if(v[i]) {
            fp << i << std::endl;
            primesWritten++;
        }
    }
}

int main (void) {
    clock_t t;
    unsigned int primesFound;
    std::ofstream fp;
    std::vector<bool> numeros(MAXIMO, true);

    t = clock();
    vectorDiscardNonPrimes(numeros);

    fp.open(OUTPUT_FILE_PATH);
    if (!fp.is_open()) {
        std::cerr << "ERROR: No se pudo abrir `" OUTPUT_FILE_PATH "`\n";
        return -1;
    }

    vectorExportToFilePath(numeros, fp, primesFound);
    fp.close();

    t = (clock() - t) / CLOCKS_PER_SEC;
    std::cout << std::fixed
              << std::setprecision(3)
              << "Se encontrarón `" << primesFound
              << "` numeros primos en `"
              << (double)(clock() - t) / CLOCKS_PER_SEC
              << "` " << " segundos\n";

    return 0;
}
