#include <iostream>
#include <iomanip>
#include <vector>

void vector_print(std::vector<int> v) {
    std::cout << "[";
    for(size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i] << ((v.size() == i+1) ? "" : ", ");
    }
    std::cout << "]\n";
}

int vector_mean(std::vector<int> v) {
    int res = 0;
    for(size_t i = 0; i < v.size(); ++i)
        res += v[i];

    return ((float)res)/v.size();
}

int main (void) {
    int n, mean, total_mean;
    unsigned int len;

    std::cout << "Cantidad de lotes> ";
    std::cin >> len;
    if (std::cin.fail()) {
        std::cerr << "Solo se permite ingresar números\n";
        return -1;
    }

    std::vector<std::vector<int>> lista(len);
    for(size_t i = 0; i < len; ++i) {
        std::cout << "Ingrese numeros de lote `" << i
                  << "`\nAl finalizar el lote ingrese `0`\n";
        while(std::cin >> n) {
            std::cout << "\033[1A\033[2K";
            if(n == 0)
                break;
                                          
            lista[i].push_back(n);
            vector_print(lista[i]);
        }
    }

    std::cout << std::endl;
    mean = total_mean = 0;
    for(size_t i = 0; i < len; ++i) {
        std::cout << std::setw(2) << i+1 << ": ";
        vector_print(lista[i]);
        std::cout << "-> mean: "
                  << (mean = vector_mean(lista[i])) << "\n\n";
        total_mean += mean;
    }

    std::cout << "=> total mean: " << total_mean << std::endl;
    return 0;
}
