#include "all_test.hpp"

#include <fmt/color.h>
#include <fmt/core.h>
#include <string>

#include "cpu_test.hpp"
#include "interpreter_test.hpp"
#include "utility/test_logger.hpp"
#include "utility/test_utils.hpp"
#include "utility/time.hpp"

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

  fmt::print("All test ");

  static constexpr const char *PASS = "PASS";
  static constexpr const char *FAIL = "FAIL";
  const char *const is_pass = ALL_GOOD ? PASS : FAIL;
  fmt::print((ALL_GOOD ? fg(fmt::color::green) : fg(fmt::color::red)), "{} ",
             is_pass);

  fmt::print(" in {} seconds.\n", Time);
  return ALL_GOOD ? TEST_RESULT::ALL_PASS : TEST_RESULT::FAILED;
}
} // namespace CPU6502_TEST
