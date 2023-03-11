

#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>

using namespace std;

int main() {
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds
    while (true) {
        system("clear && echo \"$(date '+%D %T' | toilet -f term -F border --gay)\"");
        sleep_for(nanoseconds(10));
        sleep_until(system_clock::now() + seconds(1));
    }
    return 0;
}