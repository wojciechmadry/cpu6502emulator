#include "cpu.hpp"
namespace cpu6502 {

    void CPU::JMPabsolute(u32& Cycles) noexcept
    {
        // 2 cycles
        cpu_reg.PC.set(fetch_word(Cycles));
        // 0 cycles
    }

    void CPU::JMPindirect(u32& Cycles) noexcept
    {
        // 4 cycles
        Word Address = fetch_word(Cycles);
        // 2 cycles
        cpu_reg.PC.set(read_word(Address, Cycles));
        // 0 cycles
    }

}