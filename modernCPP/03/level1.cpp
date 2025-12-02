#include <print>    // C++23 print-style formatted output
#include <vector>
#include <ranges>

// This level demonstrates simple C++23 features and <print>
int main() {
  // A simple vector of ints
  std::vector<int> values {1, 2, 3, 4, 5};
  
  // Sructured binding + ranged-for 
  // (C++17+ but still common and useful in modern code)
  for (const auto& v : values) {
    std::print("Value: {}\n", v);
  }

  // C++20 ranges + C++23 views
  // Transform each number by doubling it
  auto doubled_view = values | std::views::transform([](int x) {return x * 2;});

  std::print("\nDoubled values:\n");
  for (auto d : doubled_view)
    std::print("{} ", d);

  std::print("\n");

  // constexpr function in C++23 - computed at compile time 
  constexpr int add(int a, int b) { return a + b; }

  constexpr int result = add(10, 20);
  std::print("constexpr result = {}\n", result);
   
  return 0;
}
