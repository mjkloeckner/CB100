#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>

#define VECTOR_ELEMENT_LIMIT    20

// El vector debe tener un tamaño definido
void vector_random_populate(std::vector<int>& v) {
    srand (time(NULL));
    for(size_t i = 0; i < v.size(); ++i)
        v[i] = (int)(rand() % VECTOR_ELEMENT_LIMIT);
}

void vector_print(const std::vector<int> v) {
    std::cout << "[";
    for(size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i] << ((v.size() == i+1) ? "" : ", ");
    }
    std::cout << "]\n";
}

// Se considera que el vector siempre tiene mas de 3 elementos
void vector_find_max(std::vector<int> v, std::vector<int>& max) {
    std::sort(v.begin(), v.end());
    for(size_t i = 0; i<max.size(); ++i)
        max[i] = v[v.size()-(1+i)];
}

int main (void) {
    std::vector<int> max(3);
    std::vector<int> list(10); 

    vector_random_populate(list);
    list[list.size() - 1] = 0; // Por enunciado deber terminar en 0

    vector_print(list);
    vector_find_max(list, max);
    vector_print(max);

    return 0;
}
