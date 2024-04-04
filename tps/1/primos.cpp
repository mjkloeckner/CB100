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

void vectorExportToFile(
        const std::vector<bool> v,
        std::ofstream& outputFile,
        unsigned int &primesWritten) {

    primesWritten = 0;
    for (size_t i = 2; i < v.size(); ++i) {
        if(v[i]) {
            outputFile << i << std::endl;
            primesWritten++;
        }
    }
}

int main (void) {
    unsigned int startTime, primesFound;
    double totalTime;
    std::ofstream outputFile;
    std::vector<bool> numeros(MAXIMO, true);
    std::string timeUnit;

    startTime = clock();
    vectorDiscardNonPrimes(numeros);

    outputFile.open(OUTPUT_FILE_PATH);
    if (!outputFile.is_open()) {
        std::cerr << "ERROR: No se pudo abrir `" OUTPUT_FILE_PATH "`\n";
        return -1;
    }

    vectorExportToFile(numeros, outputFile, primesFound);
    outputFile.close();

    totalTime = (double)(clock() - startTime) / CLOCKS_PER_SEC;

    std::cout.precision(2);
    timeUnit.assign("segundos");
    if(totalTime < 1) {
        totalTime *= 1000;
        timeUnit.assign("ms");
        std::cout.precision(0);
    }

    std::cout << std::fixed
              << "Se encontraron `" << primesFound
              << "` números primos en `"
              << totalTime << "` " << timeUnit << std::endl;

    return 0;
}
