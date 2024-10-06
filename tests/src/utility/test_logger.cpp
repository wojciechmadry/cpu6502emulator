#include "utility/test_logger.hpp"
#include <print>

void log_test(const std::string_view test_name, bool is_test_passed) {
  static constexpr const char *PASS = "PASS";
  static constexpr const char *FAIL = "FAIL";
  std::print("Test {} :", test_name);
  const char *color = is_test_passed ? "[32m" : "[31m";
  std::print("\033{}{}\033[0m\n", color, (is_test_passed ? PASS : FAIL));
}
