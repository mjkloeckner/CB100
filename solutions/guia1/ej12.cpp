#include <iostream>
#include <ctime>

int main (void) {
    unsigned long in_time_secs;

    std::cin >> in_time_secs;

    time_t seconds(in_time_secs);
    tm *p = gmtime(&seconds);

    std::cout << p->tm_yday << " days, "
        << p->tm_hour << ":"
        << p->tm_min << ":"
        << p->tm_sec << std::endl;

    return 0;
}
