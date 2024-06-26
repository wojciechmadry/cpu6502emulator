#include "utility/test_logger.hpp"

#include <fmt/color.h>
#include <fmt/core.h>

void log_test(const std::string_view test_name, bool is_test_passed) {
  static constexpr const char *PASS = "PASS";
  static constexpr const char *FAIL = "FAIL";
  fmt::print("Test {} : ", test_name);
  fmt::print((is_test_passed ? fg(fmt::color::green) : fg(fmt::color::red)),
             "{}\n", (is_test_passed ? PASS : FAIL));
}
