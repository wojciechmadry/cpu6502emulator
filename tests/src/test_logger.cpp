#include "test_logger.hpp"

#include <iostream>

void log_message(const std::string_view message) noexcept
{
    std::cout << message;
}

void log_test(const std::string_view test_name, bool is_test_passed) noexcept
{
    std::cout << "Test '" << test_name << "' : ";
    if (is_test_passed)
    {
        std::cout << "PASS";
    }
    else
    {
        std::cout << "FAIL";
    }
    std::cout << '\n';
}