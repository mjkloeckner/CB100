#include <iostream>
#include <iomanip>

int fahrenheit_to_celcius(int F) {
    return ((float)5/9)*(F-32);
}

int main (void) {

    for(float i = 0; i <= 200; i += 10) 
        std::cout << std::setw(4) << i << "°F\t" 
            << std::setw(3) << fahrenheit_to_celcius(i) << "°C\n";

    return 0;
}
