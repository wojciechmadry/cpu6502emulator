#include "cpu.hpp"
namespace cpu6502 {

    void CPU::JMPabsolute(u32& Cycles) noexcept
    {
        cpu_reg.PC.set(fetch_word(Cycles));
    }

    void CPU::JMPindirect(u32& Cycles) noexcept
    {
        const Word Address = fetch_word(Cycles);
        cpu_reg.PC.set(read_word(Address, Cycles));
    }

}