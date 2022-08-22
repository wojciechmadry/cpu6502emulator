#include "utility/test_logger.hpp"

#include <fmt/core.h>       
#include <fmt/color.h>       

void log_test(const std::string_view test_name, bool is_test_passed) noexcept
{
    static constexpr const char* PASS = "PASS";
    static constexpr const char* FAIL = "FAIL";
    fmt::print("Test {} : ", test_name);
    fmt::print(
        (is_test_passed ? fg(fmt::color::green) : fg(fmt::color::red)),
        "{}\n",
        (is_test_passed ? PASS : FAIL)
        );

}
