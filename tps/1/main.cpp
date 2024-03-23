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

int main (void) {
    unsigned long ti, i, j;
    double tt;
    std::ofstream fp;
    std::vector<bool> numeros(MAXIMO, true);

    ti = clock();
	numeros[0] = numeros[1] = false; // 0 y 1 no son primos

    for (i = 2; i < std::sqrt(MAXIMO); ++i) {
        if(numeros[i]) {
            for (j = i; j <= (MAXIMO/i); ++j) {
                numeros[i*j] = false;
            }
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
    tt = (double(clock() - ti)) / CLOCKS_PER_SEC;

    std::cout.precision(2);
    std::string t_unit = "segundos";
    if(tt < 1) {
        tt *= 1000;
        t_unit.assign("ms");
        std::cout.precision(0);
    }

    std::cout << std::fixed
              << "Se encontraron `" << j 
              << "` numeros primos en `"
              << tt << "` " << t_unit << std::endl;

    return 0;
}
