#include <iostream>
#include <string>
#include <vector>

struct Salario {
    std::string nombre;
    unsigned int monto;
};

std::vector<struct Salario> data = {
    {"Juan",   850000},
    {"Elena",  200000},
    {"Ana",    525000},
    {"Carlos", 700000},
    {"Luis",   300000},
    {"Laura",  800000},
    {"Andrea", 250000},
    {"Diego",  500000},
    {"María",  900000},
    {"Pedro",  600000}
};

unsigned int find_min_index() {
    unsigned int min, min_index;

    min_index = 0;
    min = data[min_index].monto;
    for(size_t i = 0; i < data.size(); ++i) {
        if(data[i].monto < min) {
            min = data[i].monto;
            min_index = i;
        }
    }

    return min_index;
}

unsigned int find_max_index() {
    unsigned int max, max_index;

    max_index = 0;
    max = data[max_index].monto;
    for(size_t i = 0; i < data.size(); ++i) {
        if(data[i].monto > max) {
            max = data[i].monto;
            max_index = i;
        }
    }

    return max_index;
}

int main (void) {
    for(size_t i = 0; i < data.size(); ++i)
        std::cout << data[i].nombre << "\t $" << data[i].monto << std::endl;

    unsigned int min_index = find_min_index();
    unsigned int max_index = find_max_index();

    std::cout << "* Salario minimo:\t" << data[min_index].nombre
        << "\t$" << data[min_index].monto << "\n";
    std::cout << "* Salario maximo:\t" << data[max_index].nombre
        << "\t$" << data[max_index].monto << "\n";

    return 0;
}
