#include <iostream>

int product_r(int x, int y) {
    if(!x || !y)
        return 0;

    return (y < 0) ? -product_r(x, -y) : x+product_r(x, y-1);
}

int main (void) {
    std::cout << product_r(-1, -1) << std::endl;
    return 0;
}
