#include <iostream>
#include <print>
#include <thread>
#include <chrono>

int main() {
    using namespace std::chrono_literals;

    auto wake_time = std::chrono::steady_clock::now() + 3s;
    std::cout << "Sleeping until 3 seconds from now..." << std::endl;

    std::this_thread::sleep_until(wake_time);

    std::cout << "Woke up!" << std::endl;

    return 0;
}


