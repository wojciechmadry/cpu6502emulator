#include "test_logger.hpp"

#include <iostream>

void log_message(const std::string_view message, const std::string_view color) noexcept
{
    std::cout << color << message << Colors::RESET;
}

void log_test(const std::string_view test_name, bool is_test_passed) noexcept
{
    std::cout << "Test '" << test_name << "' : ";
    if (is_test_passed)
    {
        std::cout << Colors::GREEN << "PASS";
    }
    else
    {
        std::cout << Colors::RED << "FAIL";
    }
    std::cout << Colors::RESET << '\n';
}