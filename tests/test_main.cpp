#include "all_test.hpp"
#include <fmt/core.h>

int main()
{
    fmt::print("--- Run test ---\n");
    const auto test_result = CPU6502_TEST::RUN_ALL_TEST();
    fmt::print("--- End test ---\n");
    return test_result == CPU6502_TEST::TEST_RESULT::ALL_PASS ? 0 : -1;
}