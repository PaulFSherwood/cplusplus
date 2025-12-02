#include <print>
#include <string>
#include <string_view>
#include <optional>
#include <expected> // C++23 expected
#include <cctype>

// A C++20/23 concept restricting T to arithmetic types only
template <typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

// Convert string to int safely using std::expected
std::expected<int, std::string> safe_to_int(std::string_view sv) {
  // Check if the string is numeric
  for (char c : sv) {
    if (!std::isdigit(static_cast<unsigned char>(c)))
      return std::unexpected("Error: Not a numeric string.");
  }

  // Convert normally
  return std::stoi(std::string(sv));
}

int main() {
  std::print("=== Intermediate Level ===\n");

  // Using our safe_to_int function
  auto good = safe_to_int("123");
  auto bad = safe_to_int("12a3");

  if (good) {
    std::print("Converted OK: {}\n", *good);;
  } else {
    std::print("Conversion failed: {}\n", good.error());
  }

  if (bad) {
    std::print("Converted OK: {}\n", *bad);
  } else {
    std::print("Conversion failed: {}\n", bad.error());
  }

  // Demonstrating a small concept-constrained template
  auto add = [](Arithmetic auto a, Arithmetic auto b) {
    return a + b;
  };

  std::print("add(2, 5) = {}\n", add(2,5));
  std::print("add(2.5, 3.1) = {}\n", add(2.5, 3.1));

  int num = 42;
  std::print("Number in hex = {:#x}\n", num);
  std::print("Number padded = {:0>5}\n", num);

  return 0;
}
