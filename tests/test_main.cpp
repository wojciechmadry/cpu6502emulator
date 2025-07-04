#include "all_test.hpp"
#include <print>

int main() {
  std::print("--- Run test ---\n");
  const auto test_result = CPU6502_TEST::RUN_ALL_TEST();
  std::print("--- End test ---\n");
  return test_result == CPU6502_TEST::TEST_RESULT::ALL_PASS ? 0 : -1;
}
