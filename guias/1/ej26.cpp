#include <iostream>
#include <iomanip>
#include <cmath>

typedef struct {
    float x1, x2;
} Vec2f;

bool cuadratic_has_real_roots(float a, float b, float c) {
    return ((b*b)-(4*a*c)) >= 0;
}

Vec2f cuadratic_roots(float a, float b, float c) {
    if(cuadratic_has_real_roots(a, b, c) == false)
        return (Vec2f){0,0};

    Vec2f res;
    res.x1 = ((-b)+std::sqrt((b*b)-(4*a*c)))/(2*a);
    res.x2 = ((-b)-std::sqrt((b*b)-(4*a*c)))/(2*a);
    return res;
}

int main (void) {
    float a, b, c;
    Vec2f p;

    std::cin >> a;
    std::cin >> b;
    std::cin >> c;

    p = cuadratic_roots(a,b,c);
    std::cout << "x1=" << std::left << std::setw(4) << p.x1 
              << "x2=" << std::setw(4) << p.x2 << std::endl;
    return 0;
}
