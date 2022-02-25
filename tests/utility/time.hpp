#ifndef BABEL_TIME
#define BABEL_TIME

#include <chrono>

namespace babel::TIME{

    class timer
    {
    public:
        timer() noexcept;

        /**
*  @brief  Start counting time.
*  @return No return
*/
        void start() noexcept;

        /**
*  @return Get time in seconds
*/
        [[nodiscard]]long double get_time() const noexcept;


        /**
*  @return Get time in nanoseconds
*/
        [[nodiscard]]long long get_time_ns() const noexcept;

        /**
*  @return Get time in milliseconds
*/
        [[nodiscard]]long long get_time_mili() const noexcept;

        /**
*  @return Get time in microseconds
*/
        [[nodiscard]]long long get_time_micro() const noexcept;

    private:
        std::chrono::high_resolution_clock::time_point time;
    };

}

#endif