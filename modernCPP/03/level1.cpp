#include <print>     // C++23 print-style formatted output
#include <vector>
#include <ranges>

// ------------------------------------------------------------
// GCC requires constexpr functions to be at namespace scope.
// (Clang allows them inside functions, but GCC does not.)
// ------------------------------------------------------------
constexpr int add(int a, int b) {
    return a + b;
}

int main() {
    // A simple vector of ints
    std::vector<int> values {1, 2, 3, 4, 5};

    // Structured binding + ranged-for
    for (const auto& v : values) {
        std::print("Value: {}\n", v);    // <print> replaces printf/fmtlib
    }

    // C++20/23 ranges transform view
    auto doubled_view = values | std::views::transform([](int x) { return x * 2; });

    std::print("\nDoubled values:\n");
    for (auto d : doubled_view) {
        std::print("{} ", d);
    }
    std::print("\n");

    // constexpr calculation
    constexpr int result = add(10, 20);
    std::print("constexpr result = {}\n", result);

    return 0;
}
