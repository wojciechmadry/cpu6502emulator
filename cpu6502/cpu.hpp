#ifndef CPU_6502_processor
#define CPU_6502_processor

#include "required.hpp"
#include "registers.hpp"

namespace cpu6502
{
    class CPU
    {
        cpu6502::Registers cpu_reg;
        using PSFlags = cpu6502::registers::ProcessorStatus::Flags;

    public:
        CPU() = default;
        ~CPU() = default;
    };
}

#endif