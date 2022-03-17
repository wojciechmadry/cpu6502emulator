#include "ALL_TEST.HPP"

#include <string>
#include <fmt/core.h>       
#include <fmt/color.h>   

#include "register_test.hpp"
#include "cpu_test.hpp"
#include "utility/test_logger.hpp"
#include "utility/time.hpp"
#include "utility/utility.hpp"
#include "stack_test.hpp"

namespace CPU6502_TEST
{
    void RUN_ALL_TEST() noexcept
    {
        babel::TIME::timer T;
        T.start();
        bool ALL_GOOD = true;
        ALL_GOOD &= utils::run_test(CPU6502_TEST::inner::RUN_CPU_TEST, "All cpu instruction set");
        ALL_GOOD &= utils::run_test(CPU6502_TEST::inner::RUN_REGISTER_TEST, "Register");
        ALL_GOOD &= utils::run_test(CPU6502_TEST::inner::RUN_STACK_TEST, "Stack");
        
        const auto Time = T.get_time();

        fmt::print("All test ");

        static constexpr const char* PASS = "PASS";
        static constexpr const char* FAIL = "FAIL";
        const char* const is_pass = ALL_GOOD ? PASS : FAIL;
        fmt::print(
            (ALL_GOOD ? fg(fmt::color::green) : fg(fmt::color::red)),
            "{} ", is_pass);

        fmt::print(" in {} seconds.\n", Time);
    }
}
