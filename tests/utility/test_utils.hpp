#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string_view>
#include <fmt/core.h>

#include "test_logger.hpp"
#include "cpu.hpp"


namespace CPU6502_TEST::utils
{
    template<typename Func>
    inline bool run_test(Func func, std::string_view test_name) noexcept
    {
        bool test_pass;
        try
        {
            test_pass = func();
        }
        catch(std::exception& e)
        {
            test_pass = false;
            fmt::print("Test : {} throw an exception : {}\n", test_name, e.what());
        }
        log_test(test_name, test_pass);
        return test_pass;
    };

    // Jump to 2020 memory location
    void jump_to_2020(cpu6502::CPU& cpu); 

    // Load value to acumulator
    void load_to_acu(cpu6502::CPU& cpu, cpu6502::Byte value);

    // Load value to X register
    void load_to_xreg(cpu6502::CPU& cpu, cpu6502::Byte value);

    // Load value to Y register
    void load_to_yreg(cpu6502::CPU& cpu, cpu6502::Byte value);

    // Push value to stack
    void push_to_stack(cpu6502::CPU& cpu, cpu6502::Byte value);

    // Pop value from stack into acumulator
    cpu6502::Byte pop_from_stack(cpu6502::CPU& cpu);

}

#endif // UTILITY_HPP
