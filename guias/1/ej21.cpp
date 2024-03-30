#include <iostream>
#include <vector>

void vector_print(std::vector<int> v) {
    std::cout << "[";
    for(size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i] << ((v.size() == i+1) ? "" : ", ");
    }
    std::cout << "]\n";
}

int vector_is_sorted(std::vector<int> v) {
    size_t i, j, k;

    for(i = j = k = 0; i < v.size(); ++i) {
        if(v[i] > v[j]) j++;
        if(v[i] < v[k]) k++;
    }

    return (i == (j+1)) ? 1 : ((i == (k+1)) ? -1 : 0);
}


int main (void) {
    int n;
    std::vector<int> serie;

    std::cout << "[]\n";

    while(std::cin >> n) {
        std::cout << "\033[1A";
        serie.push_back(n);
        vector_print(serie);
    }

    n = vector_is_sorted(serie);
    std::cout << ((n > 0) ? "Ordenado ascendente\n" :
                 ((n < 0) ? "Ordenado descendente\n" : "No esta ordenado\n"));

    return 0;
}
