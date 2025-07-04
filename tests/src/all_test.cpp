#include "all_test.hpp"

#include "cpu_test.hpp"
#include "interpreter_test.hpp"
#include "utility/test_logger.hpp"
#include "utility/test_utils.hpp"
#include "utility/time.hpp"
#include <print>
#include <string>

namespace CPU6502_TEST {
TEST_RESULT RUN_ALL_TEST() {
  babel::TIME::timer T;
  T.start();
  bool ALL_GOOD = true;
  ALL_GOOD &= utils::run_test(CPU6502_TEST::inner::RUN_CPU_TEST,
                              "CPU instruction summary");
  ALL_GOOD &=
      utils::run_test(CPU6502_TEST::inner::RUN_REGISTER_TEST, "CPU Register");
  ALL_GOOD &= utils::run_test(CPU6502_TEST::inner::RUN_STACK_TEST, "CPU Stack");
  ALL_GOOD &= utils::run_test(
      CPU6502_TEST::interpreter_test::RUN_INTERPRETER_TEST, "Interpreter");

  const auto Time = T.get_time();

  std::print("All test ");

  static constexpr const char *PASS = "PASS";
  static constexpr const char *FAIL = "FAIL";
  const char *const is_pass = ALL_GOOD ? PASS : FAIL;
  const char *color = is_pass ? "[32m" : "[31m";
  std::print("\033{}{}\033[0m ", color, is_pass);
  std::print(" in {} seconds.\n", Time);
  return ALL_GOOD ? TEST_RESULT::ALL_PASS : TEST_RESULT::FAILED;
}
} // namespace CPU6502_TEST
