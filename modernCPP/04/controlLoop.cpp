#include <iostream>
#include <print>

int main() {

  std::print("Start of Loop\n");
  for (int y = 0; y < 10; y++) {
    std::print("y: {}\n", y);
    for (int x = 0; x < 10; x++) {
      std::print("x: {}\n", x);
      break;
    }
  }
}
