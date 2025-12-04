#include <iostream>
#include <numeric>
#include <iterator>
#include <print>
#include <array>

int main() {
  int idOne[10];
  int idTwo[10];
  std::array<int, 10> idThree;

  for (int i = 0; i < 10; i++) {
    idOne[i] = i;
  }
  for (int i = 0; i < 10; i++) {
    if (i == 9) {
      std::print("{}\n", idOne[i]);
    } else {
      std::print("{},", idOne[i]);
    }
  }

  // Junk in the array
  for (int i = 0; i < 10; i++) {
    if (i == 9) {
      std::print("{}\n", idTwo[i]);
    } else {
      std::print("{},", idTwo[i]);
    }
  }

  // fill the array with values.
  std::iota(std::begin(idTwo), std::end(idTwo), 0); // Start from the beging of your array to the end, set the first value to 0
  for (int i = 0; i < 10; i++) {
    if (i == 9) {
      std::print("{}\n", idTwo[i]);
    } else {
      std::print("{},", idTwo[i]);
    }
  }

  std::iota(std::begin(idThree), std::end(idThree), 0);
  // out of bounds at 10
  for (int i = 0; i < 20; i++) {
    std::print("({}||",i);
    idThree.at(i) = i;
    if (i == 9) {
      std::print("{})\n", idThree[i]);
    } else {
      std::print("{}),", idThree[i]);
    }
  }

  return 0;
}
