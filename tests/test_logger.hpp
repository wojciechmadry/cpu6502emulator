#ifndef TEST_LOGGER_HPP
#define TEST_LOGGER_HPP

#include <string_view>
#include <string>
#include <type_traits>


namespace Colors{
    constexpr const char* RESET = "\033[0m";
    constexpr const char* RED = "\033[31m";
    constexpr const char* GREEN = "\033[32m";
}
        

void log_test(const std::string_view test_name, bool is_test_passed) noexcept;

void log_message(const std::string_view message, const std::string_view color = "") noexcept;

template<typename Msg>
void log_messages(const Msg& msg) noexcept
{
    using dMsg = std::decay_t<Msg>;
    if constexpr (std::is_integral_v<dMsg> || std::is_floating_point_v<dMsg>)
    {
        log_message(std::to_string(msg));
    }
    else if constexpr (!std::is_same_v<dMsg, std::string>)
    {
        log_message(std::string(msg));
    }
    else
    {
        log_message(msg);
    }
}

template<typename Msg, typename ... Msgs>
void log_messages(const Msg& msg, const Msgs& ... msgs) noexcept
{
    log_messages(msg);
    log_messages(msgs...);
}

#endif  // TEST_LOGGER_HPP
