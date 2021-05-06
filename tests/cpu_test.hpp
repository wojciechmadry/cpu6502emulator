#ifndef CPU_6502_TEST_CPU
#define CPU_6502_TEST_CPU
#include "InstructionSetTest/LDA_TEST.HPP"
#include "InstructionSetTest/RTS_JSR_TEST.HPP"
#include "InstructionSetTest/JMP_TEST.HPP"
#include "time.hpp"

namespace CPU6502_TEST::inner
{
    bool RUN_CPU_TEST() noexcept
    {
        bool all_pass = true;

        all_pass &= LDA_TEST();

        all_pass &= RTS_JSR_TEST();

        all_pass &= JMP_TEST();

        return all_pass;
    }
}
#endif