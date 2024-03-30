#include <iostream>
#include <vector>

void vector_print(std::vector<int> v) {
    std::cout << "[";
    for(size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i] << ((v.size() == i+1) ? "" : ", ");
    }
    std::cout << "]\n";
}

void vector_log(std::vector<int> v) {
    int min, max;
    size_t min_pos, max_pos, min_occ, max_occ;

    min = max = v[0];
    min_pos = max_pos = min_occ = max_occ = 0;
    for(size_t i = 0; i < v.size(); ++i) {
        if(v[i] < min) {
            min = v[i];
            min_pos = i;
            min_occ = 0;
        }
        if(v[i] > max) {
            max = v[i];
            max_pos = i;
            max_occ = 0;
        }

        min_occ += (min == v[i]) ? 1 : 0;
        max_occ += (max == v[i]) ? 1 : 0;
    }

    std::cout << "* min `" << min << "` en posición `" << min_pos
              << "` (" << min_occ << " ocurrencia)\n"
              << "* max `" << max << "` en posición `" << max_pos
              << "` (" << max_occ << " ocurrencia)\n";
}

int main (void) {
    int n;
    unsigned int len;
    std::vector<int> lista;

    std::cout << "Largo de la lista> ";
    std::cin >> len;
    if (std::cin.fail()) {
        std::cerr << "Solo se permite ingresar números\n";
        return -1;
    }

    while(lista.size() < len) {
        std::cout << lista.size() << "> ";
        std::cin >> n;
        std::cout << "\033[1A\033[2K";  // Borra el caracter ingresado 

        if (std::cin.fail()) {
            std::cout << "Solo se permite ingresar números\n";
            return -1;
        }

        lista.push_back(n);
        if(lista.size() > 1)
            std::cout << "\033[1A\033[2K";  // Borra el caracter ingresado 

        vector_print(lista);
    }

    vector_log(lista);

    return 0;
}
