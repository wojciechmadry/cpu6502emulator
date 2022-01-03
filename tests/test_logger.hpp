#ifndef TEST_LOGGER_HPP
#define TEST_LOGGER_HPP

#include <string_view>

void log_test(const std::string_view test_name, bool is_test_passed) noexcept;

void log_message(const std::string_view message) noexcept;

#endif  // TEST_LOGGER_HPP
