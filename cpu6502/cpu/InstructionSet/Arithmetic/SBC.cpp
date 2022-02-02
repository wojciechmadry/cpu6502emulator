#include "cpu.hpp"
#include <limits>

namespace cpu6502{
    void CPU::SBCimmediate(u32& Cycles) noexcept
    {
        // 1 cycles
        const auto fetched = static_cast<Byte>(~fetch_byte(Cycles) + 1);
        ADC(fetched);
    }

    void CPU::SBCzeropage(u32& Cycles) noexcept
    {
        // 2 cycles
        (void) Cycles;
    }

    void CPU::SBCzeropagex(u32& Cycles) noexcept
    {
        // 3 cycles
        (void) Cycles;
    }

    void CPU::SBCabsolute(u32& Cycles) noexcept
    {
        // 3 cycles
        (void) Cycles;
    }


    void CPU::SBCabsolutex(u32& Cycles) noexcept
    {
        // 3 cycles + 1 if page crossed
        (void) Cycles;
    }


    void CPU::SBCabsolutey(u32& Cycles) noexcept
    {
        // 3 cycles + 1 if page crossed
        (void) Cycles;
    }


    void CPU::SBCindirectx(u32& Cycles) noexcept
    {
        // 5 cycles
        (void) Cycles;
    }


    void CPU::SBCindirecty(u32& Cycles) noexcept
    {
        // 4 cycles + 1 if page crossed
        (void) Cycles;
    }

}