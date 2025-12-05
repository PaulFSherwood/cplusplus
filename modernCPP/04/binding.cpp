#include <iostream>

int main() {

  auto fooBar = std::array<int, 2> { 5, 7 };

 //  auto fooBar = std::tuple<int, int> { 5, 7 };

 //  auto fooBar = FooBar { 5, 7 };


  // BEFORE
  const auto index = std::par { 3, 5 };

  const auto row = index.fist;
  const auto column = index.second;

  // AFTER
  const auto index = std::par { 3, 5 };
  const auto& [row, column] = index;

  return 0;
}
