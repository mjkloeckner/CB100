// Taken from https://github.com/mjkloeckner/sav.git

#include <iostream>
#include <vector>

#define VECTOR_ELEMENT_LIMIT    20

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

void merge(std::vector<int>& v, int low, int middle, int high) {
    size_t n1, n2, i, j, k;

    n1 = middle - low;
    n2 = high - middle;

    int B[n1], C[n2];

    /* B holds middle low array */
    for(i = low, j = 0; i < middle; i++, j++)
        B[j] = v[i];

    /* C middle high */
    for(i = middle, j = 0; i < high; i++, j++)
        C[j] = v[i];

    /* merge B and C in order */
    for(k = low, i = j = 0; (k < high) && (i < n1) && (j < n2); k++)
        v[k] = ((B[i] <= C[j]) ? v[k] = B[i++] : C[j++]);

    while(i < n1)
        v[k++] = B[i++];

    while(j < n2)
        v[k++] = C[j++];
}


void merge_sort(std::vector<int>& v, int low, int high) {
    int middle = ((high + low) / 2);

    if((high - low) > 1) {
        merge_sort(v, low, middle);
        merge_sort(v, middle, high);
        merge(v, low, middle, high);
    }
}

int main (void) {
    std::vector<int> v(10);
    vector_random_populate(v);
    vector_print(v);
    merge_sort(v, 0, v.size());
    vector_print(v);

    return 0;
}
