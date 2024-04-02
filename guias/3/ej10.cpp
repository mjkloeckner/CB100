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

void swap(int *a, int *b)
{
    int tmp;
    tmp = (*a);
    (*a) = (*b);
    (*b) = tmp;
}

void quick_sort_partition(std::vector<int> &v, int low, int &middle, int high) {
    int i, j, pivot;
    pivot = high;

    for(i = j = low; i < high; i++)
        if(v[i] < v[pivot])
            swap(&v[j++], &v[i]);

    swap(&v[j], &v[pivot]);
    middle = j;
}

void quick_sort(std::vector<int>& v, int low, int high) {
    int pivot;

    if ((high - low) > 0) {
        quick_sort_partition(v, low, pivot, high);
        quick_sort(v, low, pivot - 1);
        quick_sort(v, pivot + 1, high);
    }
}

int main (void) {
    std::vector<int> v(10);
    vector_random_populate(v);
    vector_print(v);
    quick_sort(v, 0, v.size());
    vector_print(v);
    return 0;
}
