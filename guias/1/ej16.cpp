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
    size_t min_pos, max_pos;

    min = max = v[0];
    min_pos = max_pos = 0;
    for(size_t i = 0; i < v.size(); ++i) {
        if(v[i] < min) {
            min = v[i];
            min_pos = i;
        }
        if(v[i] > max) {
            max = v[i];
            max_pos = i;
        }
    }

    std::cout << "* min: `" << min << "` en posición: `" << min_pos << "`\n"
              << "* max: `" << max << "` en posición: `" << max_pos << "`\n";
}

int main (void) {
    int n;
    std::vector<int> serie;

    while(true) {
        std::cin >> n;
        std::cout << "\033[1A";  // Borra el caracter ingresado 

        if (std::cin.fail()) {
            std::cout << "Solo se permite ingresar números" << std::endl;
            return -1;
        }

        serie.push_back(n);
        vector_print(serie);
        vector_log(serie);
        std::cout << "\n";
    }

    return 0;
}
