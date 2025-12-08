#include <ranges>
#include <vector>
#include <iostream>

int main() {
  std::vector<int> nums{1, 2, 3, 4, 5};

  // Create a view: filter even numbers, then square them
  auto view = nums
    | std::views::filter([](int n) { return n % 2 == 0; })
    | std::views::transform([](int n) { return n * n; });

    for (int v : view) {
      std::cout << v << " "; // Output: 4 16
    }
    std::cout << std::endl;
}
