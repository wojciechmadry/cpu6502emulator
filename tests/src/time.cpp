#include "time.hpp"

namespace babel::TIME{

timer::timer() noexcept
{
    start();
}

void timer::start() noexcept
{
    time = std::chrono::high_resolution_clock::now();
}

[[nodiscard]]long double timer::get_time() const noexcept
{
    return std::chrono::duration<long double>(std::chrono::high_resolution_clock::now() - ( time )).count();
}

[[nodiscard]]long long timer::get_time_ns() const noexcept
{
    return std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::high_resolution_clock::now() - ( time )).count();
}

[[nodiscard]]long long timer::get_time_mili() const noexcept
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::high_resolution_clock::now() - ( time )).count();
}

[[nodiscard]]long long timer::get_time_micro() const noexcept
{
    return std::chrono::duration_cast<std::chrono::microseconds>(
            std::chrono::high_resolution_clock::now() - ( time )).count();
}
}